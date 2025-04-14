import rclpy
from rclpy.node import Node
from visualization_msgs.msg import Marker, MarkerArray
from messages.msg import LineSegmentList
from rclpy.parameter import Parameter

class linesegmentvisualizer(Node):
    def __init__(self):
        super().__init__("linesegmentvisualizer")

        # Declare a parameter for the topic name
        self.declare_parameter("line_topic", "/transformed_lines")
        topic_name = self.get_parameter("line_topic").value

        # Subscriber to the line segment topic
        self.line_sub = self.create_subscription(
            LineSegmentList, topic_name, self.line_callback, 10)

        # Publisher for RViz markers
        self.marker_pub = self.create_publisher(MarkerArray, "visualization_marker_array", 10)

    def line_callback(self, msg):
        marker_array = MarkerArray()
        for i, segment in enumerate(msg.segments):
            marker = Marker()
            marker.header = msg.header
            marker.ns = "line_segments"
            marker.id = i
            marker.type = Marker.LINE_STRIP
            marker.action = Marker.ADD
            marker.scale.x = 0.05  # Line width
            
            # Set color (blue)
            marker.color.r = 0.0
            marker.color.g = 0.0
            marker.color.b = 1.0
            marker.color.a = 1.0  # Fully visible

            # Set points
            marker.points = [
                self.create_point(segment.start.x, segment.start.y),
                self.create_point(segment.end.x, segment.end.y)
            ]
            
            marker_array.markers.append(marker)

        self.marker_pub.publish(marker_array)

    def create_point(self, x, y):
        from geometry_msgs.msg import Point
        point = Point()
        point.x = x
        point.y = y
        point.z = 0.0  # Keep it in 2D
        return point

def main(args=None):
    rclpy.init(args=args)
    node = linesegmentvisualizer()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()
