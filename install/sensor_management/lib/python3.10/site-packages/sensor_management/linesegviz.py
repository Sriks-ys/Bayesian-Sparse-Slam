import rclpy
from rclpy.node import Node
from visualization_msgs.msg import Marker, MarkerArray
from messages.msg import LineSegmentList
from rclpy.parameter import Parameter
from geometry_msgs.msg import Point

class Linesegviz(Node):
    def __init__(self):
        super().__init__("Linesegviz")

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

def main(args=None):
    rclpy.init(args=args)
    node = Linesegviz()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()
                  