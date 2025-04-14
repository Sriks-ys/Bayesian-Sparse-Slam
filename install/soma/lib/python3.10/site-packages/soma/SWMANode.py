import rclpy
from rclpy.node import Node
from messages.msg import LineSegmentList, LandmarkLandmarkConstraint, LandmarkLandmarkConstraintList
from visualization_msgs.msg import Marker, MarkerArray
from geometry_msgs.msg import Point
import numpy as np
from scipy.spatial import KDTree

class SWMANode(Node):
    def __init__(self):
        super().__init__('SWMANode')

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
            '/SW_landmarklandmark_cons',
            10
        )

       
        self.marker_publisher = self.create_publisher(
            MarkerArray,
            '/SW_markers',
            10
        )

     
        self.declare_parameter('knn_k', 3) 

        
        self.landmark_constraints = {}

        self.angle_threshold = np.deg2rad(15)

    def landmark_callback(self, msg):
        midpoints = np.array([[(line.start.x + line.end.x) / 2, (line.start.y + line.end.y) / 2] for line in msg.segments])
        orientations = np.array([np.arctan2(line.end.y - line.start.y, line.end.x - line.start.x) for line in msg.segments])
        header = msg.header

        if len(midpoints) < 2:
            return 

    
        new_constraints = self.compute_constraints(midpoints, orientations, header)

    
        self.publisher.publish(new_constraints)

 
        self.visualize_constraints(midpoints, new_constraints)

    def compute_constraints(self, midpoints, orientations, header):
        constraint_list = LandmarkLandmarkConstraintList()
        constraint_list.header = header

        k = self.get_parameter('knn_k').value  
        k = min(k, len(midpoints) - 1)  
        
        tree = KDTree(midpoints)
        _, indices = tree.query(midpoints, k=k + 1)  

        new_constraints = {}

        for i in range(len(midpoints)):
            for j in indices[i][1:]:  
                dx = midpoints[j][0] - midpoints[i][0]
                dy = midpoints[j][1] - midpoints[i][1]

                
                angle_diff = abs(orientations[i] - orientations[j])
                angle_diff = min(angle_diff, np.pi - angle_diff) 

              
                if angle_diff < self.angle_threshold or abs(angle_diff - np.pi/2) < self.angle_threshold:
                    covariance = [0.05, 0.0, 0.0, 0.05]  
                else:
                    covariance = [0.1, 0.0, 0.0, 0.1]  

                constraint_key = tuple(sorted((i, j)))

                if constraint_key not in self.landmark_constraints:
                    self.landmark_constraints[constraint_key] = LandmarkLandmarkConstraint(
                        landmark1_id=int(i),
                        landmark2_id=int(j),
                        dx=dx,
                        dy=dy,
                        covariance=covariance
                    )

                constraint_list.constraints.append(self.landmark_constraints[constraint_key])
                new_constraints[constraint_key] = self.landmark_constraints[constraint_key]

       
        self.landmark_constraints = new_constraints

        return constraint_list

    def visualize_constraints(self, midpoints, constraint_list):
        """Visualizes the landmark-landmark constraints as stable lines in RViz."""
        marker_array = MarkerArray()
        existing_ids = set()

        for constraint in constraint_list.constraints:
            marker_id = constraint.landmark1_id * len(midpoints) + constraint.landmark2_id
            existing_ids.add(marker_id)

            marker = Marker()
            marker.header.frame_id = "map"
            marker.header.stamp = self.get_clock().now().to_msg()
            marker.ns = "landmark_constraints"
            marker.id = marker_id
            marker.type = Marker.LINE_STRIP
            marker.action = Marker.ADD
            marker.pose.orientation.w = 1.0
            marker.scale.x = 0.05 
            marker.color.a = 1.0  
            marker.color.b = 1.0  

            point1 = Point(x=midpoints[constraint.landmark1_id][0], y=midpoints[constraint.landmark1_id][1], z=0.0)
            point2 = Point(x=midpoints[constraint.landmark2_id][0], y=midpoints[constraint.landmark2_id][1], z=0.0)
            marker.points = [point1, point2]

            marker_array.markers.append(marker)

        self.marker_publisher.publish(marker_array)


def main(args=None):
    rclpy.init(args=args)
    node = SWMANode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
