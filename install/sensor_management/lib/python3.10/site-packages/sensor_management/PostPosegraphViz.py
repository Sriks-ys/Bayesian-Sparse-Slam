import rclpy
from rclpy.node import Node
from visualization_msgs.msg import Marker, MarkerArray
from geometry_msgs.msg import Point
from std_msgs.msg import ColorRGBA
from messages.msg import PoseGraph, PoseNode, PoseConstraint, LandmarkConstraint
import numpy as np


class PostPoseGraphViz(Node):
    def __init__(self):
        super().__init__('PostPoseGraphViz')

        self.declare_parameter("pose_topic", "/pose_graph")
        topic_name = self.get_parameter("pose_topic").value

        self.declare_parameter("pub_topic", 'pose_graph_viz')
        pub_name = self.get_parameter("pub_topic").value
    
       
        self.marker_pub = self.create_publisher(MarkerArray, pub_name, 10)

        self.create_subscription(PoseGraph, topic_name, self.pose_graph_callback, 10)
    
    def pose_graph_callback(self, msg: PoseGraph):
        """Processes the pose graph and publishes visualization markers."""
        marker_array = MarkerArray()

   
        for i, node in enumerate(msg.nodes):
            marker = self.create_marker(i, node.x, node.y, 0.1, color=self.color_rgba(1.0, 0.0, 1.0, 1.0))
            marker_array.markers.append(marker)
        
  
        for i, constraint in enumerate(msg.pose_constraints):
            marker = self.create_line_marker(i + 1000, msg.nodes[constraint.pose1_id], msg.nodes[constraint.pose2_id], color=self.color_rgba(1.0, 1.0, 0.0, 1.0))
            marker_array.markers.append(marker)

      
        for i, constraint in enumerate(msg.landmark_constraints):
            if constraint.pose_id < len(msg.nodes):
                pose = msg.nodes[constraint.pose_id]
                landmark_x = pose.x + constraint.rho * np.cos(pose.theta + constraint.alpha)
                landmark_y = pose.y + constraint.rho * np.sin(pose.theta + constraint.alpha)
                
                marker = self.create_line_marker(i + 2000, pose, Point(x=landmark_x, y=landmark_y, z=0.0), color=self.color_rgba(0.0, 1.0, 1.0, 1.0))
                marker_array.markers.append(marker)

        self.marker_pub.publish(marker_array)

    def create_marker(self, marker_id, x, y, scale, color):
        """Creates a sphere marker for pose nodes."""
        marker = Marker()
        marker.header.frame_id = 'map'
        marker.id = marker_id
        marker.type = Marker.SPHERE
        marker.action = Marker.ADD
        marker.pose.position.x = x
        marker.pose.position.y = y
        marker.pose.position.z = 0.0
        marker.scale.x = scale
        marker.scale.y = scale
        marker.scale.z = scale
        marker.color = color
        return marker

    def create_line_marker(self, marker_id, start, end, color):
        """Creates a line marker for constraints."""
        marker = Marker()
        marker.header.frame_id = 'map'
        marker.id = marker_id
        marker.type = Marker.LINE_STRIP
        marker.action = Marker.ADD
        marker.scale.x = 0.05
        marker.color = color

        point1 = Point(x=start.x, y=start.y, z=0.0)
        point2 = Point(x=end.x, y=end.y, z=0.0)

        marker.points.append(point1)
        marker.points.append(point2)

        return marker

    @staticmethod
    def color_rgba(r, g, b, a):
        """Creates an RGBA color."""
        return ColorRGBA(r=r, g=g, b=b, a=a)


def main():
    rclpy.init()
    node = PostPoseGraphViz()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
