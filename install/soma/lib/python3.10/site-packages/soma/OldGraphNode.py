import rclpy
from rclpy.node import Node
from nav_msgs.msg import Odometry
from std_msgs.msg import Header
from messages.msg import (
    PoseGraph, PoseNode, PoseConstraint,
    LandmarkConstraint, LineSegmentList, LineSegment
)
import numpy as np
import geometry_msgs
from sklearn.cluster import MeanShift

class OldGraphNode(Node):
    def __init__(self):
        super().__init__('OldGraphNode')

        # Publishers
        self.pose_graph_pub = self.create_publisher(PoseGraph, '/pose_graph', 10)
        self.global_landmark_pub = self.create_publisher(LineSegmentList, '/global_landmarks', 10)

        # Subscribers
        self.create_subscription(Odometry, '/odom_fused', self.odom_callback, 10)
        self.create_subscription(LineSegmentList, '/extracted_lines', self.landmark_callback, 10)


        self.pose_nodes = []
        self.pose_constraints = []
        self.landmark_constraints = []
        self.global_landmarks = []
        self.extracted_lines = []
        self.last_pose = None
        self.pose_counter = 0
        self.landmark_constraint_dict = {} 

        self.extracted_lines_per_pose = {}
        self.recent_poses = []

        self.window_size = 10

        self.min_translation = 1.0
        
        self.lidar_noise_stddev  = 0.01

        self.endpoint_distance_threshold = 0.0001
        self.overlap_threshold = 0.01

        self.a = 0.05
        self.r = 0.05
        self.bw = 0.8

    def odom_callback(self, msg: Odometry):
        x = msg.pose.pose.position.x
        y = msg.pose.pose.position.y
        theta = self.yaw_from_quaternion(msg.pose.pose.orientation)

        covariance_matrix = np.array(msg.pose.covariance).reshape(6, 6)
        pose_covariance = covariance_matrix[:3, :3].flatten().tolist()

        if self.pose_counter == 0:
            pose_covariance = [1e-5, 0.0, 0.0, 0.0, 1e-5, 0.0, 0.0, 0.0, 1e-5]
        pose_covariance = [x for x in pose_covariance]
        new_pose = PoseNode(id=self.pose_counter, x=x, y=y, theta=theta, covariance=pose_covariance)

        
        if self.should_add_pose(new_pose):
            self.add_pose_node(new_pose, pose_covariance)

    def landmark_callback(self, msg: LineSegmentList):
        if not self.pose_nodes:
            return
        
        current_pose = self.pose_nodes[-1]
        if len(self.recent_poses) ==self.window_size:
            self.recent_poses.pop(0)
        self.recent_poses.append(current_pose)

        new_landmarks = list(msg.segments)

        self.global_landmarks, updated_ids, new_to_old_map = self.merge_landmarks(self.global_landmarks, new_landmarks)
        self.update_constraints_for_merged_landmarks(updated_ids)
        constraint_dict = self.landmark_constraint_dict
        for current_pose in self.recent_poses:
            supposedly_observable_landmark = self.get_visible_landmarks(current_pose, self.global_landmarks, 4.0)

            for segment in supposedly_observable_landmark:  # Use visible landmarks

                matched_id = None
                for i, global_seg in enumerate(self.global_landmarks):
                    if np.isclose(self.euclidean_distance(global_seg.start, segment.start), 0.0, atol=1e-3) and \
                    np.isclose(self.euclidean_distance(global_seg.end, segment.end), 0.0, atol=1e-3):
                        matched_id = i
                        break

                if matched_id is None:
                    continue

                rho, alpha = self.compute_rho_alpha(current_pose, segment)
                cov = segment.covariance
                rho_var = cov[0]
                alpha_var = cov[3]

                new_constraint = LandmarkConstraint(
                    pose_id=current_pose.id,
                    landmark_id=matched_id,
                    rho=rho,
                    alpha=alpha,
                    covariance=[rho_var, 0.0, 0.0, alpha_var]
                )
                constraint_dict[(current_pose.id, matched_id)] = new_constraint  
                self.landmark_constraints.append(new_constraint)
                
        self.publish_pose_graph()
        self.publish_global_landmarks()

    def get_visible_landmarks(self, pose, landmarks, max_distance=10.0, fov=np.radians(360)):
        """Filters landmarks that are within the robot's field of view (FoV) and range."""
        visible_landmarks = []

        for segment in landmarks:
            rho, alpha = self.compute_rho_alpha(pose, segment)

            # Check if landmark is within the max view distance
            if rho > max_distance:
                continue

            # Check if the landmark is inside the field of view
            if abs(alpha) > fov / 2:
                continue

            visible_landmarks.append(segment)

        return visible_landmarks
    
    def update_constraints_for_merged_landmarks(self, updated_landmark_ids):
        for key, constraint in self.landmark_constraint_dict.items():
            if constraint.landmark_id in updated_landmark_ids:
                pose = self.pose_nodes[constraint.pose_id]
                segment = self.global_landmarks[constraint.landmark_id]
                rho, alpha = self.compute_rho_alpha(pose, segment)
                constraint.rho = rho
                constraint.alpha = alpha
    
    def should_merge(self, segment1, segment2):
        """Checks if two line segments should be merged based on projected overlap and endpoint distance."""
        # Compute projected overlap
        proj_overlap = self.compute_projected_overlap(segment1, segment2)

        # Check endpoint distance
        start_dist = self.euclidean_distance(segment1.start, segment2.start)
        end_dist = self.euclidean_distance(segment1.end, segment2.end)

        return proj_overlap >= self.overlap_threshold and (start_dist < self.endpoint_distance_threshold or end_dist < self.endpoint_distance_threshold)
    
    def compute_line_angle(self, segment):
        """Compute the angle of a line segment from its endpoints."""
        dx = segment.end.x - segment.start.x
        dy = segment.end.y - segment.start.y
        return np.arctan2(dy, dx)  # Angle in radians

    def merge_landmarks(self, global_landmarks, new_landmarks):
        all_landmarks = global_landmarks + new_landmarks

        if not all_landmarks:
            return [], set(), {}

        feature_matrix = []

        for seg in all_landmarks:
            mid_x = (seg.start.x + seg.end.x) / 2
            mid_y = (seg.start.y + seg.end.y) / 2
            rho, alpha = self.compute_rho_alpha_for_line(seg.start.x, seg.start.y, seg.end.x, seg.end.y)

            if rho < 0:
                rho = -rho
                alpha = (np.pi + alpha) % (2 * np.pi)

            feature_matrix.append([mid_x, mid_y, rho * self.r, alpha * self.a])

        clustering = MeanShift(bandwidth=self.bw).fit(feature_matrix)
        labels = clustering.labels_

        label_to_index = {label: i for i, label in enumerate(labels[:len(global_landmarks)])}  # Existing landmark indices

        merged_segments = global_landmarks[:]  # Copy existing landmarks
        unique_labels = set(labels)
        updated_ids = set()
        new_to_old_map = {}  # {new_idx (in new_landmarks) : merged_idx (in global_landmarks)}

        for label in unique_labels:
            cluster_indices = [i for i in range(len(all_landmarks)) if labels[i] == label]
            cluster_segments = [all_landmarks[i] for i in cluster_indices]
            line_params = self.hough_transform(cluster_segments)

            if line_params:
                merged_segment = self.create_merged_line(cluster_segments, line_params)

                if label in label_to_index:
                    updated_index = label_to_index[label]
                    merged_segments[updated_index] = merged_segment
                    updated_ids.add(updated_index)

                    # Map new landmark indices to the existing global landmark index
                    for i in cluster_indices:
                        if i >= len(global_landmarks):  # it's from new_landmarks
                            new_idx = i - len(global_landmarks)
                            new_to_old_map[new_idx] = updated_index
                else:
                    merged_segments.append(merged_segment)
                    new_index = len(merged_segments) - 1
                    updated_ids.add(new_index)

                    # Map new landmark indices to this new landmark
                    for i in cluster_indices:
                        if i >= len(global_landmarks):
                            new_idx = i - len(global_landmarks)
                            new_to_old_map[new_idx] = new_index

        return merged_segments, updated_ids, new_to_old_map


    def hough_transform(self, cluster_segments):
        """Performs Hough Transform to detect lines from the set of segments."""
        points = [(seg.start.x, seg.start.y, seg.end.x, seg.end.y) for seg in cluster_segments]
        line_params = []

        for start_x, start_y, end_x, end_y in points:
            rho, alpha = self.compute_rho_alpha_for_line(start_x, start_y, end_x, end_y)
            line_params.append((rho, alpha))
        return line_params

    def compute_rho_alpha_for_line(self, start_x, start_y, end_x, end_y):
        """Compute rho and alpha for a single line segment."""
        dx = end_x - start_x
        dy = end_y - start_y

        alpha = np.arctan2(dy, dx)
        rho = (start_x * np.cos(alpha)) + (start_y * np.sin(alpha))

        return rho, alpha

    def create_merged_line(self, cluster_segments, line_params):
        avg_rho = np.mean([param[0] for param in line_params])
        avg_alpha = np.mean([param[1] for param in line_params])

        # Now compute the start and end points of the new merged line using the rho, alpha values
        x_min, x_max = np.min([seg.start.x for seg in cluster_segments]), np.max([seg.end.x for seg in cluster_segments])
        y_min, y_max = np.min([seg.start.y for seg in cluster_segments]), np.max([seg.end.y for seg in cluster_segments])

        cov = [x for x in cluster_segments[0].covariance]

        merged_segment = LineSegment(
            rho=avg_rho,  # Mean rho
            alpha=avg_alpha,  # Mean alpha
            covariance=cov,  # Assuming covariance is the same for simplicity
            start=geometry_msgs.msg.Point(x=x_min, y=y_min, z=0.0),
            end=geometry_msgs.msg.Point(x=x_max, y=y_max, z=0.0)
        )
        return merged_segment

    
    def compute_projected_overlap(self, seg1, seg2):
        """Computes the projected overlap between two segments along their shared line."""
        seg1_length = self.euclidean_distance(seg1.start, seg1.end)
        seg2_length = self.euclidean_distance(seg2.start, seg2.end)
        x_min = max(min(seg1.start.x, seg1.end.x), min(seg2.start.x, seg2.end.x))
        x_max = min(max(seg1.start.x, seg1.end.x), max(seg2.start.x, seg2.end.x))

        overlap_length = max(0, x_max - x_min)
        return overlap_length / min(seg1_length, seg2_length)

    def euclidean_distance(self, p1, p2):
        """Computes Euclidean distance between two points."""
        return np.sqrt((p1.x - p2.x) ** 2 + (p1.y - p2.y) ** 2)

    def should_add_pose(self, new_pose: PoseNode):
        if self.last_pose is None:
            return True

        dx = new_pose.x - self.last_pose.x
        dy = new_pose.y - self.last_pose.y
        dtheta = abs(new_pose.theta - self.last_pose.theta)

        distance = np.sqrt(dx**2 + dy**2)

        return distance > self.min_translation
    
    def find_matching_landmark_id(self, segment):
        for i, lm in enumerate(self.global_landmarks):
            if self.euclidean_distance(lm.start, segment.start) < 1e-3 and \
            self.euclidean_distance(lm.end, segment.end) < 1e-3:
                return i
        return None
    
    def compute_rho_alpha(self, pose, segment):
        """Computes rho and alpha of a landmark relative to a given pose."""
        mid_x = (segment.start.x + segment.end.x) / 2
        mid_y = (segment.start.y + segment.end.y) / 2

        dx = mid_x - pose.x
        dy = mid_y - pose.y

        # Rotate into pose's local frame
        cos_theta = np.cos(-pose.theta)
        sin_theta = np.sin(-pose.theta)

        local_x = cos_theta * dx - sin_theta * dy
        local_y = sin_theta * dx + cos_theta * dy

        rho = np.sqrt(local_x**2 + local_y**2)
        alpha = np.arctan2(local_y, local_x)  # No need to subtract pose.theta anymore

        return rho, alpha


    def add_pose_node(self, new_pose: PoseNode, odom_covariance):
        if self.last_pose:
            dx = new_pose.x - self.last_pose.x
            dy = new_pose.y - self.last_pose.y
            dtheta = new_pose.theta - self.last_pose.theta
            constraint_covariance = odom_covariance

            constraint = PoseConstraint(
                pose1_id=self.last_pose.id,
                pose2_id=new_pose.id,
                dx=dx,
                dy=dy,
                dtheta=dtheta,
                covariance=constraint_covariance
            )
            self.pose_constraints.append(constraint)
        self.pose_nodes.append(new_pose)
        self.last_pose = new_pose
        self.pose_counter += 1
        self.extracted_lines_per_pose[new_pose.id] = self.extracted_lines.copy()

    def publish_pose_graph(self):
        """Publishes the constructed pose graph."""
        graph_msg = PoseGraph(
            header=Header(frame_id='map'),
            nodes=self.pose_nodes,
            pose_constraints=self.pose_constraints,
            landmark_constraints=list(self.landmark_constraint_dict.values())
        )
        self.pose_graph_pub.publish(graph_msg)

    def publish_global_landmarks(self):
        """Publishes the cumulative global landmark list."""
        landmark_msg = LineSegmentList(header=Header(frame_id='map'), segments=self.global_landmarks)
        self.global_landmark_pub.publish(landmark_msg)

    def match_extracted_to_global(self, extracted_lines, global_landmarks):
        matched_landmarks = {}

        for extracted in extracted_lines:
            best_match = None
            best_error = float('inf')

            for i, landmark in enumerate(global_landmarks):
                alpha_diff = abs(extracted.alpha - landmark.alpha)
                rho_diff = abs(extracted.rho - landmark.rho)
                error = alpha_diff + rho_diff

                if error < best_error:
                    best_error = error
                    best_match = i  # Index of best-matching global landmark

            if best_match is not None and best_match not in matched_landmarks:
                matched_landmarks[best_match] = global_landmarks[best_match]

        return matched_landmarks

    @staticmethod
    def yaw_from_quaternion(q):
        """Extracts yaw from a quaternion."""
        import math
        siny_cosp = 2 * (q.w * q.z + q.x * q.y)
        cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z)
        return math.atan2(siny_cosp, cosy_cosp)

def main():
    rclpy.init()
    node = OldGraphNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '_main_':
    main()