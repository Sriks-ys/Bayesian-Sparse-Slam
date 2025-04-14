import rclpy
from rclpy.node import Node
import numpy as np
from nav_msgs.msg import OccupancyGrid
from geometry_msgs.msg import Pose, Point, Quaternion
from std_msgs.msg import Header

from messages.msg import LineSegmentList

class LandmarkMapGenerator(Node):
    def __init__(self):
        super().__init__('landmark_map_generator')

        # Parameters
        self.map_resolution = 0.05  # meters per cell
        self.map_width = 2000  # cells
        self.map_height = 2000  # cells
        self.map_origin_x = -50.0  # meters
        self.map_origin_y = -50.0  # meters

        # Map publisher
        self.map_pub = self.create_publisher(OccupancyGrid, '/slam_occupancy_map', 10)

        # Landmark subscriber
        self.landmark_sub = self.create_subscription(
            LineSegmentList,
            '/global_landmarks',
            self.landmark_callback,
            10
        )

    def landmark_callback(self, msg):
        grid = -np.ones((self.map_height, self.map_width), dtype=np.int8)

        for segment in msg.segments:
            start = segment.start
            end = segment.end
            points = self.sample_line(start, end, spacing=self.map_resolution / 2.0)
            for pt in points:
                mx = int((pt[0] - self.map_origin_x) / self.map_resolution)
                my = int((pt[1] - self.map_origin_y) / self.map_resolution)
                if 0 <= mx < self.map_width and 0 <= my < self.map_height:
                    grid[my, mx] = 100

        self.publish_map(grid)

    def sample_line(self, start: Point, end: Point, spacing: float):
        dx = end.x - start.x
        dy = end.y - start.y
        length = np.hypot(dx, dy)
        num_points = int(length / spacing) + 1
        return [
            (start.x + i * dx / num_points, start.y + i * dy / num_points)
            for i in range(num_points + 1)
        ]

    def publish_map(self, grid):
        grid_msg = OccupancyGrid()
        grid_msg.header = Header()
        grid_msg.header.stamp = self.get_clock().now().to_msg()
        grid_msg.header.frame_id = 'map'

        grid_msg.info.resolution = self.map_resolution
        grid_msg.info.width = self.map_width
        grid_msg.info.height = self.map_height
        grid_msg.info.origin = Pose()
        grid_msg.info.origin.position.x = self.map_origin_x
        grid_msg.info.origin.position.y = self.map_origin_y
        grid_msg.info.origin.position.z = 0.0
        grid_msg.info.origin.orientation = Quaternion(w=1.0)

        # Flatten in row-major order
        grid_msg.data = grid.flatten().tolist()
        self.map_pub.publish(grid_msg)

def main(args=None):
    rclpy.init(args=args)
    node = LandmarkMapGenerator()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
