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
from sklearn.linear_model import HuberRegressor, LinearRegression
import numpy as np
import geometry_msgs.msg


class GraphNode(Node):
    def __init__(self):
        super().__init__('GraphNode')

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

        self.sliding_window_size = 3
        self.recent_poses = []  # keeps track of recent pose IDs


        self.extracted_lines_per_pose = {}

        self.min_translation = 1.25
        self.min_rotation = np.radians(30)

        self.lidar_noise_stddev  = 0.01

        self.endpoint_distance_threshold = 0.0001
        self.overlap_threshold = 0.01
        self.bw = 0.8

        self.r = 0.01
        self.a = 0.01

    def odom_callback(self, msg: Odometry):
        x = msg.pose.pose.position.x
        y = msg.pose.pose.position.y
        theta = self.yaw_from_quaternion(msg.pose.pose.orientation)

        covariance_matrix = np.array(msg.pose.covariance).reshape(6, 6)
        pose_covariance = covariance_matrix[:3, :3].flatten().tolist()

        if self.pose_counter == 0:
            pose_covariance = [1e-5, 0.0, 0.0, 0.0, 1e-5, 0.0, 0.0, 0.0, 1e-5]

        new_pose = PoseNode(id=self.pose_counter, x=x, y=y, theta=theta, covariance=pose_covariance)

        if self.should_add_pose(new_pose):
            self.add_pose_node(new_pose, pose_covariance)

    def landmark_callback(self, msg: LineSegmentList):
        if not self.pose_nodes:
            return
        
        current_pose = self.pose_nodes[-1]
        if len(self.recent_poses) == self.sliding_window_size:
            self.recent_poses.append(current_pose)
            self.recent_poses.pop(0)
        else:
            self.recent_poses.append(current_pose)

        new_landmarks = list(msg.segments)

        self.global_landmarks, updated_ids = self.merge_landmarks(self.global_landmarks, new_landmarks)

        self.update_constraints_for_merged_landmarks(updated_ids)
        constraint_dict = {(c.pose_id, c.landmark_id): c for c in self.landmark_constraints}

        for current_pose in self.recent_poses:

            supposedly_observable_landmark = self.get_visible_landmarks(current_pose, self.global_landmarks, 3.0)

            for segment in supposedly_observable_landmark:  # Use visible landmarks
                
                try:
                    landmark_id = self.global_landmarks.index(segment)
                except ValueError:
                    continue
                
                #landmark_id = self.find_matching_landmark_id(segment)
                if landmark_id is None:
                    continue

                if (current_pose.id, landmark_id) in constraint_dict:
                    existing_constraint = constraint_dict[(current_pose.id, landmark_id)]
                    existing_constraint.rho, existing_constraint.alpha = self.compute_rho_alpha(current_pose, segment)
                else:

                    rho, alpha = self.compute_rho_alpha(current_pose, segment)

                    cov = segment.covariance
                    rho_var = cov[0]
                    alpha_var = cov[3]

                    head = Header()
                    head.frame_id = 'Crawler/base_link/LinSense'
                    new_constraint = LandmarkConstraint(
                        header = head,
                        pose_id=current_pose.id,
                        landmark_id=landmark_id,
                        rho=rho,
                        alpha=alpha,
                        covariance=[rho_var, 0.0, 0.0, alpha_var]
                    )
                    self.landmark_constraints.append(new_constraint)
                    
        self.publish_pose_graph()
        self.publish_global_landmarks()

    def get_visible_landmarks(self, pose, landmarks, max_distance=10.0, fov=np.radians(360)):
        """Filters landmarks that are within the robot's field of view (FoV) and range."""
        visible_landmarks = []

        for segment in landmarks:
            rho, alpha = self.compute_rho_alpha(pose, segment)
            if rho > max_distance:
                continue
            if abs(alpha) > fov / 2:
                continue

            visible_landmarks.append(segment)

        return visible_landmarks
    
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
    
    def group_by_orientation(self, segments, angle_thresh=np.radians(20)):
        filtered_groups = []
        used_segments = set()
        for i, base_seg in enumerate(segments):
            if i in used_segments:
                continue

            group = [base_seg]
            used_segments.add(i)

            for j, seg in enumerate(segments):
                if j in used_segments or i == j:
                    continue

                angle_diff = abs((seg.alpha - base_seg.alpha + np.pi) % (2 * np.pi) - np.pi)
                if angle_diff < angle_thresh:
                    group.append(seg)
                    used_segments.add(j)

            if len(group) > 1:
                filtered_groups.append(group)

        return filtered_groups
    
    def compute_line_angle(self, segment):
        """Compute the angle of a line segment from its endpoints."""
        dx = segment.end.x - segment.start.x
        dy = segment.end.y - segment.start.y
        return np.arctan2(dy, dx) 
    
    def update_constraints_for_merged_landmarks(self, updated_landmark_ids):
        for constraint in self.landmark_constraints:
            if constraint.landmark_id in updated_landmark_ids:
                pose = self.pose_nodes[constraint.pose_id]
                segment = self.global_landmarks[constraint.landmark_id]
                rho, alpha = self.compute_rho_alpha(pose, segment)
                constraint.rho = rho
                constraint.alpha = alpha

    def merge_landmarks(self, global_landmarks, new_landmarks):
        all_landmarks = global_landmarks + new_landmarks

        if not all_landmarks:
            return [], set()
        
        feature_matrix = []

        for seg in all_landmarks:
            rho = seg.rho
            alpha = seg.alpha

            mid_X, mid_Y = (seg.start.x + seg.end.x) / 2, (seg.start.y + seg.end.y) / 2
            if rho < 0:
                rho = -rho  
            alpha = alpha % np.pi
            feature_matrix.append([mid_X, mid_Y, alpha*self.a, rho*self.r])

        clustering = MeanShift(bandwidth=self.bw).fit(feature_matrix)  
        labels = clustering.labels_

        label_to_index = {label: i for i, label in enumerate(labels[:len(global_landmarks)])}  # Map original indices

        merged_segments = global_landmarks[:]  # Copy existing landmarks
        unique_labels = set(labels)
        updated_ids = set()

        for label in unique_labels:
            cluster_segments = [all_landmarks[i] for i in range(len(all_landmarks)) if labels[i] == label]
            orientation_group = self.group_by_orientation(cluster_segments)
            
            for group in orientation_group:
                if len(group) < 2:
                    continue
                line_params = self.hough_transform(group)

                if not line_params:
                    continue
                
                merged_segment = self.create_merged_line(group)

                if label in label_to_index:
                    updated_index = label_to_index[label]
                    merged_segments[updated_index] = merged_segment
                    updated_ids.add(updated_index)
                else:
                    merged_segments.append(merged_segment)  
                    updated_ids.add(len(merged_segments) - 1)

        return merged_segments, updated_ids

    def hough_transform(self, cluster_segments):
        """Performs Hough Transform to detect lines from the set of segments."""
        points = [(seg.start.x, seg.start.y, seg.end.x, seg.end.y) for seg in cluster_segments]
        line_params = []

        for start_x, start_y, end_x, end_y in points:
            rho, alpha = self.compute_rho_alpha_for_line(start_x, start_y, end_x, end_y)
            line_params.append((rho, alpha))
        return line_params

    def compute_rho_alpha_for_line(self, start_x, start_y, end_x, end_y):
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

        merged_segment = LineSegment(
            rho=avg_rho,  # Mean rho
            alpha=avg_alpha,  # Mean alpha
            covariance=cluster_segments[0].covariance,  # Assuming covariance is the same for simplicity
            start=geometry_msgs.msg.Point(x=x_min, y=y_min, z=0.0),
            end=geometry_msgs.msg.Point(x=x_max, y=y_max, z=0.0)
        )
        return merged_segment


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
            landmark_constraints=self.landmark_constraints
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

    @staticmethod
    def yaw_from_quaternion(q):
        """Extracts yaw from a quaternion."""
        import math
        siny_cosp = 2 * (q.w * q.z + q.x * q.y)
        cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z)
        return math.atan2(siny_cosp, cosy_cosp)

def main():
    rclpy.init()
    node = GraphNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()