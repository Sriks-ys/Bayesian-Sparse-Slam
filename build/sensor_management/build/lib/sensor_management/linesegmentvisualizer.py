import rclpy
from rclpy.node import Node
from visualization_msgs.msg import Marker, MarkerArray
from messages.msg import LineSegmentList
from rclpy.parameter import Parameter
from geometry_msgs.msg import Point

class LineSegmentVisualizer(Node):
    def __init__(self):
        super().__init__("LineSegmentVisualizer")

        # Declare a parameter for the topic name
        self.declare_parameter("line_topic", "/extracted_lines")
        topic_name = self.get_parameter("line_topic").value

        self.declare_parameter("pub_topic", '/landmark_constraints_viz')
        pub_name = self.get_parameter("pub_topic").value

        # Subscriber to the line segment topic
        self.line_sub = self.create_subscription(
            LineSegmentList, topic_name, self.line_callback, 10)

       
        self.marker_pub = self.create_publisher(MarkerArray, pub_name, 10)
        self.c = 0

    def line_callback(self, msg):
       
        self.clear_markers()

        marker_array = MarkerArray()
        for i, segment in enumerate(msg.segments):
            marker = Marker()
            marker.header = msg.header
            marker.ns = "line_segments"
            marker.id = i
            marker.type = Marker.LINE_STRIP
            marker.action = Marker.ADD
            marker.scale.x = 0.05
            
          
            
            if self.c == 0: 
                marker.color.r = 1.0
                marker.color.g = 0.0
                marker.color.b = 0.0
                marker.color.a = 1.0
                self.c += 1

            elif self.c == 1:
                marker.color.r = 0.0
                marker.color.g = 1.0
                marker.color.b = 0.0
                marker.color.a = 1.0
                self.c += 1

            elif self.c == 2:
                marker.color.r = 0.0
                marker.color.g = 0.0
                marker.color.b = 1.0
                marker.color.a = 1.0
                self.c += 1
            else: 
                marker.color.r = 1.0
                marker.color.g = 1.0
                marker.color.b = 1.0
                marker.color.a = 1.0
                self.c = 0
    
            marker.points = [
                self.create_point(segment.start.x, segment.start.y),
                self.create_point(segment.end.x, segment.end.y)
            ]
            
            marker_array.markers.append(marker)
            text_marker = Marker()
            text_marker.header = msg.header
            text_marker.ns = "line_segment_text"
            text_marker.id = i + 10000  # Use a unique id for text markers
            text_marker.type = Marker.TEXT_VIEW_FACING
            text_marker.action = Marker.ADD
            text_marker.scale.z = 0.4  # Size of the text
            text_marker.color.r = 1.0  # Red color for the text
            text_marker.color.g = 1.0  # Green color for the text
            text_marker.color.b = 0.0  # Blue color for the text
            text_marker.color.a = 1.0  # Fully opaque

            # Calculate the midpoint of the line segment
            midpoint = self.compute_midpoint(segment)
            text_marker.pose.position = midpoint
            text_marker.text = str(i)  # Text is the index of the line segment

            marker_array.markers.append(text_marker)

        self.marker_pub.publish(marker_array)

    def create_point(self, x, y):
        point = Point()
        point.x = x
        point.y = y
        point.z = 0.0 
        return point

    def clear_markers(self):
        """Publish an empty MarkerArray to clear previous markers."""
        empty_array = MarkerArray()
        self.marker_pub.publish(empty_array)

    def compute_midpoint(self, segment):
        """Computes the midpoint of a line segment."""
        midpoint = Point()
        midpoint.x = (segment.start.x + segment.end.x) / 2.0
        midpoint.y = (segment.start.y + segment.end.y) / 2.0
        midpoint.z = 0.0  # Keep it on the same plane
        return midpoint

def main(args=None):
    rclpy.init(args=args)
    node = LineSegmentVisualizer()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()
