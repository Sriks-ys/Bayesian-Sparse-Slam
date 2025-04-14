import rclpy
from rclpy.node import Node
from visualization_msgs.msg import Marker, MarkerArray
from std_msgs.msg import Header
from messages.msg import LandmarkLandmarkConstraintList, LineSegmentList
import numpy as np
from geometry_msgs.msg import Point

class LandmarkConstraintVisualizer(Node):
    def __init__(self):
        super().__init__('landmark_constraint_visualizer')
        
        # Subscribers
        self.subscription = self.create_subscription(
            LandmarkLandmarkConstraintList,
            '/bayes_lm_lm',
            self.constraint_callback,
            10
        )
        self.landmark_subscription = self.create_subscription(
            LineSegmentList,
            '/global_landmarks',
            self.landmark_callback,
            10
        )
        
        # Publisher
        self.marker_pub = self.create_publisher(MarkerArray, '/landmark_constraints_markers', 10)
        
        self.landmarks = {}
        
    def landmark_callback(self, msg):
        """ Stores global landmarks for midpoint computation. """
        self.landmarks = {i: seg for i, seg in enumerate(msg.segments)}

        
    def constraint_callback(self, msg):
        """ Processes landmark constraints and publishes visualization markers. """
        marker_array = MarkerArray()
        
        for i, constraint in enumerate(msg.constraints):
            landmark1 = self.landmarks.get(constraint.landmark1_id)
            landmark2 = self.landmarks.get(constraint.landmark2_id)

            if landmark1 is None or landmark2 is None:
                continue  # Skip this constraint

            
            if landmark1 and landmark2:
                midpoint1 = self.compute_midpoint(landmark1)
                midpoint2 = self.compute_midpoint(landmark2)
                
                # Line Marker
                line_marker = Marker()
                line_marker.header = Header(frame_id='map', stamp=self.get_clock().now().to_msg())
                line_marker.ns = 'lmc'
                line_marker.id = i
                line_marker.type = Marker.LINE_STRIP
                line_marker.action = Marker.ADD
                line_marker.scale.x = 0.05
                
                probability = 1.0 / (1.0 + float(np.linalg.det(np.array(constraint.covariance).reshape(2, 2))))
                line_marker.color.r = probability # More confident = darker
                line_marker.color.g = 0.0
                line_marker.color.b = 1.0 - probability
                line_marker.color.a = 1.0
                
                p1 = Point(x=midpoint1.x, y=midpoint1.y, z=0.0)
                p2 = Point(x=midpoint2.x, y=midpoint2.y, z=0.0)

                line_marker.points = [p1, p2]
                marker_array.markers.append(line_marker)
    
        self.marker_pub.publish(marker_array)
    
    def compute_midpoint(self, landmark):
        """ Computes the midpoint of a line segment. """
        midpoint = landmark.start
        midpoint.x = (landmark.start.x + landmark.end.x) / 2.0
        midpoint.y = (landmark.start.y + landmark.end.y) / 2.0
        return midpoint


def main(args=None):
    rclpy.init(args=args)
    node = LandmarkConstraintVisualizer()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
