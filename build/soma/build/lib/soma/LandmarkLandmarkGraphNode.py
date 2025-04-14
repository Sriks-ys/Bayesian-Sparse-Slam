import rclpy
from rclpy.node import Node
from messages.msg import LineSegmentList
from messages.msg import LandmarkLandmarkConstraint, LandmarkLandmarkConstraintList
import numpy as np

class LandmarkLandmarkGraphNode(Node):
    def __init__(self):
        super().__init__('landmark_landmark_graph_node')
        self.subscription = self.create_subscription(
            LineSegmentList,
            '/landmark_graph',
            self.landmark_callback,
            10
        )
        self.publisher = self.create_publisher(
            LandmarkLandmarkConstraintList,
            '/landmark_landmark_graph',
            10
        )

    def landmark_callback(self, msg):
        midpoints = [[(line.start.x + line.end.x) / 2, (line.start.y + line.end.y) / 2] for line in msg.segments]
        constraints = self.compute_constraints(midpoints)
        self.publisher.publish(constraints)

    def compute_constraints(self, midpoints):
        constraint_list = LandmarkLandmarkConstraintList()
        constraint_list.header.frame_id = 'map'
        for i in range(len(midpoints)):
            for j in range(i + 1, len(midpoints)):
                dx = midpoints[j][0] - midpoints[i][0]
                dy = midpoints[j][1] - midpoints[i][1]
                covariance = [0.1, 0.0, 0.0, 0.1]  # Example covariance
                
                constraint = LandmarkLandmarkConstraint()
                constraint.landmark1_id = i
                constraint.landmark2_id = j
                constraint.dx = dx
                constraint.dy = dy
                constraint.covariance = covariance
                constraint_list.constraints.append(constraint)
        return constraint_list


def main(args=None):
    rclpy.init(args=args)
    node = LandmarkLandmarkGraphNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
