import rclpy
from rclpy.node import Node
from sensor_msgs.msg import PointCloud2
from nav_msgs.msg import Odometry
from std_msgs.msg import Header
from messages.msg import LineSegment, LineSegmentList
import pcl
import numpy as np
from sensor_msgs_py import point_cloud2

class Ransac(Node):
    def __init__(self):
        super().__init__('Ransac')
        self.sub = self.create_subscription(PointCloud2, '/acc_filter', self.scan_callback, 10)
        self.pub = self.create_publisher(LineSegmentList, '/extracted_lines', 10)
        self.odom_sub = self.create_subscription(Odometry, '/odom_fused', self.odom_callback, 10)
        self.current_angular_velocity = 0.0
        self.angular_velocity_threshold = 0.2
        self.distance_threshold = 0.95
        self.get_logger().info('RANSAC Line Extraction Node initialized.')

    def odom_callback(self, msg):
        self.current_angular_velocity = abs(msg.twist.twist.angular.z)

    def scan_callback(self, msg):
        if self.current_angular_velocity > self.angular_velocity_threshold:
            return

        points = [tuple(p[:2]) for p in point_cloud2.read_points(msg, field_names=("x", "y"), skip_nans=True)]
        clusters = self.cluster_points(points)
        line_segments = [self.fit_line_ransac(cluster) for cluster in clusters if len(cluster) > 1]
        self.publish_lines([seg for seg in line_segments if seg], msg.header)

    def cluster_points(self, points):
        if not points:
            return []

        clusters = []
        current_cluster = [points[0]]

        for i in range(1, len(points)):
            dist = np.hypot(points[i][0] - points[i - 1][0], points[i][1] - points[i - 1][1])
            if dist > self.distance_threshold:
                clusters.append(current_cluster)
                current_cluster = []
            current_cluster.append(points[i])

        if current_cluster:
            clusters.append(current_cluster)
        
        return clusters

    def fit_line_ransac(self, cluster):
        cloud = pcl.PointCloud()
        cloud.from_list([(p[0], p[1], 0.0) for p in cluster])
        model = pcl.SampleConsensusModelLine(cloud)
        ransac = pcl.RandomSampleConsensus(model)
        ransac.set_DistanceThreshold(0.1)
        if not ransac.computeModel():
            return None
        coeffs = ransac.getModelCoefficients()
        x0, y0, _, dx, dy, _ = coeffs
        
        projections = [(p[0] - x0) * dx + (p[1] - y0) * dy for p in cluster]
        min_proj, max_proj = min(projections), max(projections)
        start, end = (x0 + min_proj * dx, y0 + min_proj * dy), (x0 + max_proj * dx, y0 + max_proj * dy)
        return start, end

    def publish_lines(self, segments, header):
        line_list = LineSegmentList()
        line_list.header = header
        for start, end in segments:
            line = LineSegment()
            line.start.x, line.start.y = start
            line.end.x, line.end.y = end
            line.rho = np.hypot(*start)
            line.alpha = np.arctan2(start[1], start[0])
            line_list.segments.append(line)
        self.pub.publish(line_list)


def main(args=None):
    rclpy.init(args=args)
    node = Ransac()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == '__main__':
    main()
