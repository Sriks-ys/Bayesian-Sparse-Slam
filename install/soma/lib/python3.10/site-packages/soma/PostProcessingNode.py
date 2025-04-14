import rclpy
from rclpy.node import Node
from nav_msgs.msg import Odometry
from std_msgs.msg import Header
from sensor_msgs.msg import LaserScan
from messages.msg import (
    PoseGraph, PoseNode, PoseConstraint,
    LandmarkConstraint, LineSegmentList, LineSegment
)
from geometry_msgs.msg import Point
import numpy as np
from sklearn.cluster import DBSCAN

class PostProcessingNode(Node):
    def __init__(self):
        super().__init__('PostProcessingNode')

        
        # Publishers
        self.processed_pose_graph_pub = self.create_publisher(PoseGraph, '/pose_graph_processed', 10)
        self.processed_global_landmark_pub = self.create_publisher(LineSegmentList, '/global_landmarks_processed', 10)

        

        # Subscribers
        self.create_subscription(PoseGraph, '/pose_graph', self.pose_graph_callback, 10)
        self.create_subscription(LineSegmentList, '/global_landmarks', self.global_landmark_callback, 10)

     
        self.pose_nodes = []
        self.landmark_constraints = []
        self.global_landmarks = []
        self.pose_counter = 0

 
        self.min_poses_for_processing = 3  
        self.dbscan_eps = 0.1  
        self.dbscan_min_samples = 2  

    def pose_graph_callback(self, msg: PoseGraph):
        """Updates the pose graph and triggers landmark processing if enough poses exist."""
        self.pose_nodes = list(msg.nodes)
        self.landmark_constraints = list(msg.landmark_constraints)

        if len(self.pose_nodes) >= self.min_poses_for_processing:
            self.process_landmarks()

    def global_landmark_callback(self, msg: LineSegmentList):
        """Updates the global landmark list."""
        self.global_landmarks = list(msg.segments)

    def process_landmarks(self):
        """Applies DBSCAN clustering and line fitting to reduce redundant landmarks."""
        if len(self.pose_nodes) < self.min_poses_for_processing:
            return

   
        recent_poses = self.pose_nodes[-2:-1]  
        landmarks_to_process = []
        for pose in recent_poses:
            landmarks_to_process.extend(self.get_landmarks_for_pose(pose.id))

        
        clustered_landmarks = self.cluster_and_merge(landmarks_to_process)

        
        self.update_pose_graph(recent_poses, clustered_landmarks)

        
        self.publish_processed_pose_graph()
        self.publish_processed_global_landmarks()

    def get_landmarks_for_pose(self, pose_id):
        """Extracts landmarks associated with a given pose."""
        return [lm for lm in self.global_landmarks if any(lc.pose_id == pose_id for lc in self.landmark_constraints)]

    def cluster_and_merge(self, landmarks):
        """Clusters and merges landmarks using DBSCAN, then fits one line per cluster."""
        if not landmarks:
            return []

        
        points = np.array([(seg.start.x, seg.start.y) for seg in landmarks] +
                          [(seg.end.x, seg.end.y) for seg in landmarks])

        clustering = DBSCAN(eps=self.dbscan_eps, min_samples=self.dbscan_min_samples).fit(points)
        labels = clustering.labels_

        unique_clusters = set(labels) - {-1}  
        merged_segments = []

        for cluster_id in unique_clusters:
            cluster_points = points[labels == cluster_id]
            merged_segment = self.fit_line_to_cluster(cluster_points)
            merged_segments.append(merged_segment)

        return merged_segments

    def fit_line_to_cluster(self, cluster_points):
        """Fits a single line segment to a set of clustered points."""
        x_vals = cluster_points[:, 0]
        y_vals = cluster_points[:, 1]

        
        A = np.vstack([x_vals, np.ones(len(x_vals))]).T
        m, c = np.linalg.lstsq(A, y_vals, rcond=None)[0]

        
        min_x, max_x = np.min(x_vals), np.max(x_vals)
        min_y, max_y = m * min_x + c, m * max_x + c

        start = Point(x=min_x, y=min_y)
        end = Point(x=max_x, y=max_y)

        return LineSegment(
            rho=np.mean([seg.rho for seg in cluster_points if hasattr(seg, 'rho')]),
            alpha=np.mean([seg.alpha for seg in cluster_points if hasattr(seg, 'alpha')]),
            covariance=[0] * 4,  
            start=start,
            end=end
        )

    def update_pose_graph(self, processed_poses, new_landmarks):
        """Updates the pose graph with the newly processed landmarks."""
        for pose in processed_poses:
            pose_landmarks = self.get_landmarks_for_pose(pose.id)
            new_constraints = []

            for i, segment in enumerate(new_landmarks):
                constraint = LandmarkConstraint(
                    pose_id=pose.id,
                    landmark_id=i,
                    rho=segment.rho,
                    alpha=segment.alpha,
                    covariance=list(segment.covariance)
                )
                new_constraints.append(constraint)

            self.landmark_constraints = [
                lc for lc in self.landmark_constraints if lc.pose_id != pose.id
            ] + new_constraints

    def publish_processed_pose_graph(self):
        """Publishes the updated pose graph with processed landmarks."""
        graph_msg = PoseGraph(
            header=Header(frame_id='map'),
            nodes=self.pose_nodes,
            pose_constraints=[],
            landmark_constraints=self.landmark_constraints
        )
        self.processed_pose_graph_pub.publish(graph_msg)

    def publish_processed_global_landmarks(self):
        """Publishes the updated cumulative global landmark list."""
        landmark_msg = LineSegmentList(header=Header(frame_id='map'), segments=self.global_landmarks)
        self.processed_global_landmark_pub.publish(landmark_msg)

def main():
    rclpy.init()
    node = PostProcessingNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
