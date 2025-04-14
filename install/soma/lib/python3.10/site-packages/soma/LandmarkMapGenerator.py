import rclpy
from rclpy.qos import QoSProfile, QoSDurabilityPolicy, QoSReliabilityPolicy
from rclpy.node import Node
from messages.msg import LineSegmentList
from nav_msgs.msg import OccupancyGrid
import numpy as np
import cv2
import os

class LandmarkMapGenerator(Node):
    def __init__(self):
        super().__init__('landmark_to_occupancy_node')

        # Subscription to optimized landmarks
        self.subscription = self.create_subscription(
            LineSegmentList,
            '/optimized_landmarks',
            self.landmark_callback,
            10
        )

        qos_profile_transient = QoSProfile(
            reliability=QoSReliabilityPolicy.RELIABLE,
            durability=QoSDurabilityPolicy.TRANSIENT_LOCAL,
            depth=1
        )
        
        # Subscription to ground truth map
        self.map_subscription = self.create_subscription(
            OccupancyGrid,
            '/map',
            self.map_callback,
            qos_profile_transient
        )

        # Initialize variables for storing maps
        self.generated_map = None
        self.ground_truth_map = None

        # Map configuration
        self.resolution = 0.05
        self.origin = (-9.83, -9.83)
        self.map_size_m = 25.0
        self.map_size_px = int(self.map_size_m / self.resolution)
        self.height = self.width = self.map_size_px
        self.save_path = '/home/kvothe/ros/results'  # change as needed

        self.get_logger().info("Landmark to Occupancy Map node initialized.")

    def world_to_grid(self, x, y):
        gx = int((x - self.origin[0]) / self.resolution)
        gy = int((y - self.origin[1]) / self.resolution)
        gy = self.height - gy - 1  # Flip for image coords
        return gx, gy

    def landmark_callback(self, msg):
        # Initialize empty occupancy grid
        grid = np.zeros((self.height, self.width), dtype=np.uint8)

        for segment in msg.segments:
            x1, y1 = segment.start.x, segment.start.y
            x2, y2 = segment.end.x, segment.end.y

            p1 = self.world_to_grid(x1, y1)
            p2 = self.world_to_grid(x2, y2)

            if self.valid_point(p1) and self.valid_point(p2):
                cv2.line(grid, p1, p2, color=255, thickness=1)

        self.generated_map = grid
        self.save_map(grid)

        # If ground truth is available, calculate metrics
        if self.ground_truth_map is not None:
            self.compute_metrics(self.generated_map, self.ground_truth_map)

    def valid_point(self, pt):
        x, y = pt
        return 0 <= x < self.width and 0 <= y < self.height

    def save_map(self, grid):
        map_img_path = os.path.join(self.save_path, 'bayes.pgm')
        yaml_path = os.path.join(self.save_path, 'bayes.yaml')

        # Save PGM (invert for ROS convention: 0=occupied, 255=free)
        cv2.imwrite(map_img_path, 255 - grid)

        with open(yaml_path, 'w') as f:
            f.write(f"""image: bayes.pgm
mode: trinary
resolution: {self.resolution}
origin: [{self.origin[0]}, {self.origin[1]}, 0]
negate: 0
occupied_thresh: 0.65
free_thresh: 0.25
""")

        self.get_logger().info(f"Saved occupancy map to {map_img_path} and {yaml_path}")

    def map_callback(self, msg):
        # Convert OccupancyGrid to numpy array
        self.width = msg.info.width
        self.height = msg.info.height
        self.resolution = msg.info.resolution
        self.origin = (msg.info.origin.position.x, msg.info.origin.position.y)


        self.ground_truth_map = np.array(msg.data).reshape((self.height, self.width))


    def compute_metrics(self, generated_map, ground_truth_map):
        # Compute accuracy: percentage of correct pixels
        correct_pixels = np.sum(generated_map == ground_truth_map)
        total_pixels = generated_map.size
        accuracy = correct_pixels / total_pixels * 100

        # Compute IoU: Intersection / Union
        intersection = np.sum((generated_map > 0) & (ground_truth_map > 0))
        union = np.sum((generated_map > 0) | (ground_truth_map > 0))
        iou = intersection / union if union > 0 else 0

        # Compute confusion matrix components
        true_positive = np.sum((generated_map > 0) & (ground_truth_map > 0))
        false_positive = np.sum((generated_map > 0) & (ground_truth_map == 0))
        false_negative = np.sum((generated_map == 0) & (ground_truth_map > 0))
        true_negative = np.sum((generated_map == 0) & (ground_truth_map == 0))

        # Log the results
        self.get_logger().info(f"Accuracy: {accuracy:.2f}%")
        self.get_logger().info(f"IoU: {iou:.4f}")
        self.get_logger().info(f"True Positives: {true_positive}")
        self.get_logger().info(f"False Positives: {false_positive}")
        self.get_logger().info(f"False Negatives: {false_negative}")
        self.get_logger().info(f"True Negatives: {true_negative}")

        # Save metrics to a text file
        metrics_file = os.path.join(self.save_path, 'metrics.txt')
        with open(metrics_file, 'w') as f:
            f.write(f"Accuracy: {accuracy:.2f}%\n")
            f.write(f"IoU: {iou:.4f}\n")
            f.write(f"True Positives: {true_positive}\n")
            f.write(f"False Positives: {false_positive}\n")
            f.write(f"False Negatives: {false_negative}\n")
            f.write(f"True Negatives: {true_negative}\n")
        self.get_logger().info(f"Metrics saved to {metrics_file}")

def main(args=None):
    rclpy.init(args=args)
    node = LandmarkMapGenerator()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


