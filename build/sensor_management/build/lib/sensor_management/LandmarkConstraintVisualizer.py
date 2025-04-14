import rclpy
from rclpy.node import Node
from visualization_msgs.msg import Marker, MarkerArray
from geometry_msgs.msg import Point
from messages.msg import LandmarkConstraint
from std_msgs.msg import Header

class LandmarkConstraintVisualizer(Node):
    def __init__(self):
        super().__init__('landmark_constraint_visualizer')

        self.declare_parameter("con_topic", "/Eu_landmarklandmark_cons")
        topic_name = self.get_parameter("con_topic").value

        self.declare_parameter("pub_topic", '/landmark_constraints_viz')
        pub_name = self.get_parameter("pub_topic").value
        
        # Subscriber to Landmark Constraints
        self.subscription = self.create_subscription(
            LandmarkConstraint, topic_name, self.constraint_callback, 10)
        
        # Publisher for visualization
        self.marker_pub = self.create_publisher(MarkerArray, pub_name, 10)
        
        self.get_logger().info("Landmark Constraint Visualizer Node Initialized")
    
    def constraint_callback(self, msg: LandmarkConstraint):
        marker_array = MarkerArray()
        
        # Create a marker for the constraint line
        line_marker = Marker()
        line_marker.header = Header()
        line_marker.header.stamp = self.get_clock().now().to_msg()
        line_marker.header.frame_id = 'map'  # Ensure this matches your correct frame
        line_marker.ns = "landmark_constraints"
        line_marker.id = msg.landmark1_id * 1000 + msg.landmark2_id  # Unique ID
        line_marker.type = Marker.LINE_STRIP
        line_marker.action = Marker.ADD
        line_marker.scale.x = 0.05  # Line width
        line_marker.color.a = 1.0  # Fully opaque
        line_marker.color.r = 1.0  # Red color for constraints
        line_marker.pose.orientation.w = 1.0  # No rotation
        
        # Get the actual landmark positions (assuming a separate topic holds landmark positions)
        # For now, using placeholder values
        p1 = Point(x=float(msg.landmark1_id), y=float(msg.landmark1_id), z=0.0)  # Replace with actual landmark positions
        p2 = Point(x=float(msg.landmark1_id) + msg.dx, y=float(msg.landmark1_id) + msg.dy, z=0.0)  # Adjusted position
        
        line_marker.points.append(p1)
        line_marker.points.append(p2)
        
        marker_array.markers.append(line_marker)
        
        # Publish the visualization markers
        self.marker_pub.publish(marker_array)

        self.get_logger().info(f"Published landmark constraint between {msg.landmark1_id} and {msg.landmark2_id}")


def main(args=None):
    rclpy.init(args=args)
    node = LandmarkConstraintVisualizer()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
