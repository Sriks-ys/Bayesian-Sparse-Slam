import rclpy
from rclpy.node import Node
from sensor_msgs.msg import LaserScan, PointCloud2
from sensor_msgs_py import point_cloud2
import numpy as np
import math

class SparseSampler(Node):
    def __init__(self):
        super().__init__('sparsesampler')

        self.subscription = self.create_subscription(
            LaserScan,
            '/scan', 
            self.scan_callback,
            10
        )

        self.pointcloud_publisher = self.create_publisher(
            PointCloud2,
            '/sparse_scan',  
            10
        )

        self.laserscan_publisher = self.create_publisher(
            LaserScan,
            '/sparse_laser_scan',  
            10
        )

        self.num_points = 4

    def scan_callback(self, msg: LaserScan):
        num_points = len(msg.ranges)
        if num_points < self.num_points:
            self.get_logger().warn("Not enough points in scan to downsample to 11 points!")
            return
        
        
        indices = np.linspace(0, num_points - 1, self.num_points, dtype=int)

        points = []
        downsampled_ranges = []  
        for i in indices:
            range_val = msg.ranges[i]
            if math.isinf(range_val) or math.isnan(range_val) or range_val < msg.range_min or range_val > msg.range_max:
                continue  

            angle = msg.angle_min + i * msg.angle_increment
            x = range_val * math.cos(angle)
            y = range_val * math.sin(angle)
            z = 0.0  
            points.append((x, y, z))
            downsampled_ranges.append(range_val)  

        
        pointcloud_msg = point_cloud2.create_cloud_xyz32(msg.header, points)
       
        self.pointcloud_publisher.publish(pointcloud_msg)

        sparse_scan_msg = LaserScan()
        sparse_scan_msg.header = msg.header  
        sparse_scan_msg.angle_min = msg.angle_min
        sparse_scan_msg.angle_max = msg.angle_max
        sparse_scan_msg.angle_increment = msg.angle_increment * (num_points - 1) / len(downsampled_ranges)  
        sparse_scan_msg.scan_time = msg.scan_time
        sparse_scan_msg.range_min = msg.range_min
        sparse_scan_msg.range_max = msg.range_max
        sparse_scan_msg.ranges = downsampled_ranges  
        sparse_scan_msg.intensities = []  

       
        self.laserscan_publisher.publish(sparse_scan_msg)
        
def main(args=None):
    rclpy.init(args=args)
    node = SparseSampler()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
