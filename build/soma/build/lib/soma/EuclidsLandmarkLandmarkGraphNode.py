import rclpy
from rclpy.node import Node
from messages.msg import LineSegmentList, LandmarkLandmarkConstraintList, LandmarkLandmarkConstraint
from visualization_msgs.msg import Marker, MarkerArray
from geometry_msgs.msg import Point
import numpy as np
from scipy.spatial import KDTree

class EuclidsLandmarkLandmarkGraphNode(Node):
    def __init__(self):
        super().__init__('EuclidsLandmarkLandmarkGraphNode')

        # Subscriber to receive LineSegmentList
        self.subscription = self.create_subscription(
            LineSegmentList,
            '/global_landmarks',
            self.landmark_callback,
            10
        )

        # Publisher for LandmarkLandmarkConstraintList
        self.publisher = self.create_publisher(
            LandmarkLandmarkConstraintList,
            '/Eu_landmarklandmark_cons',
            10
        )

        # Publisher for visualizing the constraints in RViz2
        self.marker_publisher = self.create_publisher(
            MarkerArray,
            '/Eu_markers',
            10
        )

        
        self.declare_parameter('knn_k', 3)  

    def landmark_callback(self, msg):
        
        midpoints = np.array([[(line.start.x + line.end.x) / 2, (line.start.y + line.end.y) / 2] for line in msg.segments])
        header = msg.header

        if len(midpoints) < 2:
            
            return

       
        new_constraints = self.compute_constraints(midpoints, header)

        
        self.publisher.publish(new_constraints)

        
        self.visualize_constraints(midpoints, new_constraints)

    def compute_constraints(self, midpoints, header):
        constraint_list = LandmarkLandmarkConstraintList()
        constraint_list.header = header
        
        k = self.get_parameter('knn_k').value  
        k = min(k, len(midpoints) - 1) 

       
        tree = KDTree(midpoints)
        _, indices = tree.query(midpoints, k=k + 1)  
        
        for i in range(len(midpoints)):
            for j in indices[i][1:]:  
                dx = midpoints[j][0] - midpoints[i][0]
                dy = midpoints[j][1] - midpoints[i][1]
                covariance = [0.1, 0.0, 0.0, 0.1]  
                constraint = LandmarkLandmarkConstraint()
                constraint.header = header
                constraint.landmark1_id = int(i)
                constraint.landmark2_id = int(j)
                constraint.dx = dx
                constraint.dy = dy
                constraint.covariance = covariance
                constraint_list.constraints.append(constraint)
        
        return constraint_list

    def visualize_constraints(self, midpoints, constraint_list):
        """Visualizes the landmark-landmark constraints as lines in RViz."""
        marker_array = MarkerArray()

        for constraint in constraint_list.constraints:
            marker = Marker()
            marker.header.frame_id = "map"
            marker.header.stamp = self.get_clock().now().to_msg()
            marker.ns = "landmark_constraints"
            marker.id = constraint.landmark1_id * len(midpoints) + constraint.landmark2_id
            marker.type = Marker.LINE_STRIP
            marker.action = Marker.ADD
            marker.pose.orientation.w = 1.0
            marker.scale.x = 0.05  
            
          
            marker.color.a = 1.0  
            marker.color.g = 1.0 

           
            point1 = Point(x=midpoints[constraint.landmark1_id][0], y=midpoints[constraint.landmark1_id][1], z=0.0)
            point2 = Point(x=midpoints[constraint.landmark2_id][0], y=midpoints[constraint.landmark2_id][1], z=0.0)

            marker.points = [point1, point2]
            
            marker_array.markers.append(marker)

        self.marker_publisher.publish(marker_array)


def main(args=None):
    rclpy.init(args=args)
    node = EuclidsLandmarkLandmarkGraphNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
