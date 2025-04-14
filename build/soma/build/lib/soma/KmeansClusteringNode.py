import rclpy
from rclpy.node import Node
from sensor_msgs.msg import PointCloud2
from sensor_msgs_py import point_cloud2
import pcl
import numpy as np
from sklearn.cluster import KMeans
import struct

class KMeansClusteringNode(Node):
    def __init__(self):
        super().__init__('KMeansClusteringNode')
        self.subscription = self.create_subscription(
            PointCloud2,
            '/acc_filter',
            self.scan_callback,
            10)
        self.publisher = self.create_publisher(PointCloud2, '/clustered_points', 10)
        self.n_clusters = 5  # Number of clusters, can be tuned
        self.get_logger().info("KMeans Clustering Node Initialized")

    def scan_callback(self, msg):
        points = []
        for p in point_cloud2.read_points(msg, field_names=("x", "y"), skip_nans=True):
            points.append([p[0], p[1]])
        
        if len(points) < 2:
            return  # Not enough points
        
        points = np.array(points)
        n_clusters = min(self.n_clusters, len(points))  # Ensure valid cluster count
        kmeans = KMeans(n_clusters=n_clusters, n_init='auto')
        kmeans.fit(points)
        labels = kmeans.labels_
        
        # Store points per cluster
        clustered_points = [[] for _ in range(n_clusters)]
        for i, label in enumerate(labels):
            clustered_points[label].append(points[i])
        
        # Flatten clustered points back into a single list for publishing
        clustered_flattened = np.vstack(clustered_points)
        
        # Convert back to PointCloud2
        clustered_msg = self.create_pointcloud(msg.header, clustered_flattened)
        self.publisher.publish(clustered_msg)

    def create_pointcloud(self, header, points):
        fields = [
            ('x', 0, 7, 4),  # FLOAT32
            ('y', 4, 7, 4),
            ('z', 8, 7, 4)
        ]
        
        data = []
        for p in points:
            data.append(struct.pack("fff", p[0], p[1], 0.0))  # Z = 0
        
        return PointCloud2(
            header=header,
            height=1,
            width=len(points),
            is_dense=True,
            is_bigendian=False,
            fields=[point_cloud2.PointField(name=f[0], offset=f[1], datatype=f[2], count=1) for f in fields],
            point_step=12,
            row_step=12 * len(points),
            data=b''.join(data)
        )


def main(args=None):
    rclpy.init(args=args)
    node = KMeansClusteringNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
