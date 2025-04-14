import rclpy
from rclpy.node import Node
from nav_msgs.msg import Odometry
from std_msgs.msg import Header
from sensor_msgs.msg import LaserScan
from messages.msg import PoseGraph, PoseNode, PoseConstraint, LandmarkConstraint, LineSegmentList
import numpy as np

class PoseGraphNode(Node):
    def __init__(self):
        super().__init__('PoseGraphNode')
        
        # Publishers
        self.pose_graph_pub = self.create_publisher(PoseGraph, '/pose_graph', 10)
        
        # Subscribers
        self.create_subscription(Odometry, '/odom_cv', self.odom_callback, 10)
        self.create_subscription(LineSegmentList, '/landmark_graph', self.landmark_callback, 10)
        
        # Internal storage
        self.pose_nodes = []  
        self.pose_constraints = [] 
        self.landmark_constraints = []  
        self.last_pose = None  
        self.pose_counter = 0  
        
       
        self.min_translation = 2.0  
        self.min_rotation = 0.5  
    
    def odom_callback(self, msg: Odometry):
        """Handles incoming odometry messages and determines if a new pose node should be added."""
        x = msg.pose.pose.position.x
        y = msg.pose.pose.position.y
        theta = self.yaw_from_quaternion(msg.pose.pose.orientation)
        covariance = list(msg.pose.covariance[:9])  
        
        new_pose = PoseNode(id=self.pose_counter, x=x, y=y, theta=theta, covariance=covariance)
        
        if self.should_add_pose(new_pose):
            self.add_pose_node(new_pose)
    
    def landmark_callback(self, msg: LineSegmentList):
        """Handles incoming landmark messages and associates them with the latest pose node."""
        if not self.pose_nodes:
            return  
        
        current_pose = self.pose_nodes[-1]
        for i, segment in enumerate(msg.segments):
            landmark_id = i  
            constraint = LandmarkConstraint(
                pose_id=current_pose.id,
                landmark_id=landmark_id,
                rho=segment.rho,
                alpha=segment.alpha,
                covariance=list(segment.covariance)
            )
            self.landmark_constraints.append(constraint)
        
        self.publish_pose_graph()
    
    def should_add_pose(self, new_pose: PoseNode):
        """Determines if a new pose node should be added based on movement thresholds."""
        if self.last_pose is None:
            return True  
        
        dx = new_pose.x - self.last_pose.x
        dy = new_pose.y - self.last_pose.y
        dtheta = abs(new_pose.theta - self.last_pose.theta)
        
        distance = np.sqrt(dx**2 + dy**2)
        
        return distance > self.min_translation or dtheta > self.min_rotation
    
    def add_pose_node(self, new_pose: PoseNode):
        """Adds a new pose node and creates a constraint to the previous pose if applicable."""
        if self.last_pose:
            constraint = PoseConstraint(
                pose1_id=self.last_pose.id,
                pose2_id=new_pose.id,
                dx=new_pose.x - self.last_pose.x,
                dy=new_pose.y - self.last_pose.y,
                dtheta=new_pose.theta - self.last_pose.theta,
                covariance=self.last_pose.covariance  
            )
            self.pose_constraints.append(constraint)
        
        self.pose_nodes.append(new_pose)
        self.last_pose = new_pose
        self.pose_counter += 1
        
    def publish_pose_graph(self):
        """Publishes the constructed pose graph."""

        graph_msg = PoseGraph(
            header=Header(frame_id='map'),
            nodes=self.pose_nodes,
            pose_constraints=self.pose_constraints,
            landmark_constraints=self.landmark_constraints
        )
        self.pose_graph_pub.publish(graph_msg)
    
    @staticmethod
    def yaw_from_quaternion(q):
        """Extracts yaw from a quaternion."""
        import math
        siny_cosp = 2 * (q.w * q.z + q.x * q.y)
        cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z)
        return math.atan2(siny_cosp, cosy_cosp)
    

def main():
    rclpy.init()
    node = PoseGraphNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
