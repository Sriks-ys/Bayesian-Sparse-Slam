import rclpy
from rclpy.node import Node
from geometry_msgs.msg import PoseArray, Pose
import time


class WaypointPublisher(Node):
    def __init__(self):
        super().__init__('waypoint_publisher')

        
        self.publisher = self.create_publisher(PoseArray, '/waypoints', 10)

        
        self.waypoints = [
            (4.0, 0.0, 0.0), 
            (2.0, 0.0, 0.0),  
               
        ]

        self.timer = self.create_timer(5.0, self.publish_waypoints)

    def publish_waypoints(self):
        """Publishes waypoints to the /waypoints topic."""
        msg = PoseArray()

        for x, y, yaw in self.waypoints:
            pose = Pose()
            pose.position.x = x
            pose.position.y = y
            msg.poses.append(pose)

        self.publisher.publish(msg)
        self.get_logger().info("Published waypoints!")

def main(args=None):
    rclpy.init(args=args)
    node = WaypointPublisher()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
