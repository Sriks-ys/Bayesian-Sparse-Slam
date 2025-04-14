import rclpy
from rclpy.node import Node
from visualization_msgs.msg import Marker, MarkerArray
from geometry_msgs.msg import Point
from std_msgs.msg import ColorRGBA
from messages.msg import PoseGraph, PoseNode, PoseConstraint, LandmarkConstraint
import numpy as np
import math
from geometry_msgs.msg import Quaternion


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

        # Create sphere markers for Pose Nodes
        for i, node in enumerate(msg.nodes):
            marker = self.create_arrow_marker(i, node.x, node.y, node.theta, 0.3, color=self.color_rgba(1.0, 0.0, 1.0, 1.0))
            marker_array.markers.append(marker)

            # Text Marker for Pose Node ID
            text_marker = self.create_text_marker(i + 10000, node.x, node.y, str(node.id))
            #marker_array.markers.append(text_marker)
        
        # Create line markers for Pose Constraints
        for i, constraint in enumerate(msg.pose_constraints):
            marker = self.create_line_marker(i + 1000, msg.nodes[constraint.pose1_id], msg.nodes[constraint.pose2_id], color=self.color_rgba(1.0, 1.0, 0.0, 1.0))
            marker_array.markers.append(marker)

        # Create line markers for Landmark Constraints
        for i, constraint in enumerate(msg.landmark_constraints):
            if constraint.pose_id < len(msg.nodes):
                pose = msg.nodes[constraint.pose_id]
                landmark_x = pose.x + constraint.rho * np.cos(pose.theta + constraint.alpha)
                landmark_y = pose.y + constraint.rho * np.sin(pose.theta + constraint.alpha)
                marker = self.create_line_marker(i + 2000, pose, Point(x=landmark_x, y=landmark_y, z=0.0), color=self.color_rgba(0.0, 1.0, 1.0, 1.0))
                text_id = i + 3000  # Ensure unique ID
                mid_x = (pose.x + landmark_x) / 2.0
                mid_y = (pose.y + landmark_y) / 2.0
                label = f"{constraint.pose_id}-{constraint.landmark_id}"
                text_marker = self.create_text_marker(text_id, mid_x, mid_y, label)
                #marker_array.markers.append(text_marker)
                marker_array.markers.append(marker)

        self.marker_pub.publish(marker_array)

    def create_arrow_marker(self, marker_id, x, y, theta, length, color):
        """Creates an arrow marker to represent pose with orientation."""
        marker = Marker()
        marker.header.frame_id = 'map'
        marker.id = marker_id
        marker.type = Marker.ARROW
        marker.action = Marker.ADD
        marker.scale.x = length  # shaft length
        marker.scale.y = 0.05    # shaft diameter
        marker.scale.z = 0.1     # head diameter
        marker.color = color

        marker.pose.position.x = x
        marker.pose.position.y = y
        marker.pose.position.z = 0.0

        # Convert theta (2D yaw) to quaternion
        
        q = Quaternion()
        q.z = math.sin(theta / 2.0)
        q.w = math.cos(theta / 2.0)
        marker.pose.orientation = q

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

    def create_text_marker(self, marker_id, x, y, text):
        """Creates a text marker to display Pose Node ID."""
        text_marker = Marker()
        text_marker.header.frame_id = 'map'
        text_marker.id = marker_id
        text_marker.type = Marker.TEXT_VIEW_FACING
        text_marker.action = Marker.ADD
        text_marker.pose.position.x = x
        text_marker.pose.position.y = y
        text_marker.pose.position.z = 0.1  # Slightly above the node to make it readable
        text_marker.scale.z = 0.5  # Text size
        text_marker.color = self.color_rgba(0.0, 1.0, 0.0, 1.0)  # Green color for the text
        text_marker.text = text

        return text_marker

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