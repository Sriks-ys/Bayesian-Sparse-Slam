import rclpy
from rclpy.node import Node
from visualization_msgs.msg import Marker, MarkerArray
from geometry_msgs.msg import Point
from std_msgs.msg import ColorRGBA
from messages.msg import PoseGraph

class OptiPoseViz(Node):
    def __init__(self):
        super().__init__('OptiPoseViz')
        self.subscription = self.create_subscription(
            PoseGraph, '/optimized_pose_graph', self.pose_graph_callback, 10)
        self.marker_pub = self.create_publisher(MarkerArray, '/pose_graph_markers', 10)

    def pose_graph_callback(self, msg: PoseGraph):
        marker_array = MarkerArray()
        

        for node in msg.nodes:
            marker = Marker()
            marker.header = msg.header
            marker.ns = "poses"
            marker.id = node.id
            marker.type = Marker.SPHERE
            marker.action = Marker.ADD
            marker.pose.position.x = node.x
            marker.pose.position.y = node.y
            marker.pose.position.z = 0.0
            marker.scale.x = 0.2
            marker.scale.y = 0.2
            marker.scale.z = 0.2
            marker.color = ColorRGBA(r=0.0, g=1.0, b=0.0, a=1.0) 
            marker_array.markers.append(marker)
        
       
        for constraint in msg.pose_constraints:
            line_marker = Marker()
            line_marker.header = msg.header
            line_marker.ns = "pose_edges"
            line_marker.id = constraint.pose1_id * 1000 + constraint.pose2_id
            line_marker.type = Marker.LINE_STRIP
            line_marker.action = Marker.ADD
            line_marker.scale.x = 0.05
            line_marker.color = ColorRGBA(r=1.0, g=0.0, b=0.0, a=1.0)  # Red
            
            p1 = Point(x=msg.nodes[constraint.pose1_id].x, y=msg.nodes[constraint.pose1_id].y, z=0.0)
            p2 = Point(x=msg.nodes[constraint.pose2_id].x, y=msg.nodes[constraint.pose2_id].y, z=0.0)
            line_marker.points.append(p1)
            line_marker.points.append(p2)
            
            marker_array.markers.append(line_marker)
        
        self.marker_pub.publish(marker_array)


def main():
    rclpy.init()
    node = OptiPoseViz()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
