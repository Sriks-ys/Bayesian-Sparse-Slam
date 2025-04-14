#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Imu
from nav_msgs.msg import Odometry
import numpy as np
from filterpy.kalman import ExtendedKalmanFilter as EKF
from tf_transformations import euler_from_quaternion

class Fusion(Node):
    def __init__(self):
        super().__init__('fusion')
        self.create_subscription(Odometry, '/odom', self.odom_callback, 10)
        self.create_subscription(Odometry, '/odom_cv', self.odom_cv_callback, 10)
        self.create_subscription(Imu, '/imu', self.imu_callback, 10)
        self.odom_fused_pub = self.create_publisher(Odometry, '/odom_fused', 10)
        self.ekf = EKF(dim_x=5, dim_z=3)
        self.ekf.x = np.zeros(5)
        self.ekf.P *= 1.0
        self.ekf.Q = np.diag([0.01, 0.01, 0.001, 0.1, 0.1])
        self.ekf.R = np.diag([0.02, 0.02, 0.01])
        self.last_time = self.get_clock().now()

    def f(self, x, dt):
        dt = (self.get_clock().now() - self.last_time).nanoseconds * 1e-9
        dt = max(min(dt, 0.1), 0.01)
        self.last_time = self.get_clock().now()
        x_new = np.copy(x)
        x_new[0] += x[3] * np.cos(x[2]) * dt
        x_new[1] += x[3] * np.sin(x[2]) * dt
        x_new[2] = x[2] + x[4] * dt
        return x_new

    def odom_callback(self, msg):
        dt = (self.get_clock().now() - self.last_time).nanoseconds * 1e-9
        dt = max(min(dt, 0.1), 0.01)
        self.last_time = self.get_clock().now()
        self.ekf.predict()
        v = msg.twist.twist.linear.x
        omega = msg.twist.twist.angular.z
        q = msg.pose.pose.orientation
        _, _, yaw = euler_from_quaternion([q.x, q.y, q.z, q.w])
        if abs(v) < 0.01 and abs(omega) < 0.01:
            v *= 0.5
            omega *= 0.5
        self.ekf.x[3] = v
        self.ekf.x[4] = omega
        z = np.array([msg.pose.pose.position.x, msg.pose.pose.position.y, yaw])
        self.ekf.update(z, HJacobian=self.HJacobian, Hx=self.Hx)
        self.publish_fused_odometry()

    def odom_cv_callback(self, msg):
        covariance_matrix = np.array(msg.pose.covariance).reshape(6, 6)
        scale = 2.5 if abs(self.ekf.x[3]) < 0.01 and abs(self.ekf.x[4]) < 0.01 else 1.5
        self.ekf.P[:3, :3] = covariance_matrix[:3, :3]*scale

    def imu_callback(self, msg):
        dt = (self.get_clock().now() - self.last_time).nanoseconds * 1e-9
        dt = max(min(dt, 0.1), 0.01)
        self.last_time = self.get_clock().now()
        omega = msg.angular_velocity.z
        weight = 0.3 if abs(omega) > 0.01 else 0.2
        self.ekf.x[4] = weight*omega
        self.ekf.predict()
        self.publish_fused_odometry()

    def publish_fused_odometry(self):
        fused_odom = Odometry()
        fused_odom.header.stamp = self.get_clock().now().to_msg()
        fused_odom.header.frame_id = 'odom'
        fused_odom.child_frame_id = 'base_link'

        # Set Pose
        fused_odom.pose.pose.position.x = self.ekf.x[0]
        fused_odom.pose.pose.position.y = self.ekf.x[1]
        fused_odom.pose.pose.orientation.z = np.sin(self.ekf.x[2] / 2)
        fused_odom.pose.pose.orientation.w = np.cos(self.ekf.x[2] / 2)

        # Set Twist
        fused_odom.twist.twist.linear.x = self.ekf.x[3]
        fused_odom.twist.twist.angular.z = self.ekf.x[4]

        imu_ang_stddev = 0.001 
        imu_acc_stddev = 0.0005 
        odom_stddev = 0.02 

        P = self.ekf.P.copy()  
        
        P[0, 0] += odom_stddev ** 2  
        P[1, 1] += odom_stddev ** 2   
        P[2, 2] += imu_ang_stddev ** 2  
        P[3, 3] += imu_acc_stddev ** 2   
        P[4, 4] += imu_ang_stddev ** 2   

        fused_odom.pose.covariance = [
            P[0, 0], P[0, 1], 0.0, 0.0, 0.0, P[0, 2],
            P[1, 0], P[1, 1], 0.0, 0.0, 0.0, P[1, 2],
            0.0, 0.0, 1e-4, 0.0, 0.0, 0.0,  
            0.0, 0.0, 0.0, 1e-4, 0.0, 0.0,  
            0.0, 0.0, 0.0, 0.0, 1e-4, 0.0,  
            P[2, 0], P[2, 1], 0.0, 0.0, 0.0, P[2, 2]
        ]

        fused_odom.twist.covariance = [
            P[3, 3], 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, P[3, 3], 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 1e-4, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 1e-4, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 1e-4, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, P[4, 4]
        ]


        self.odom_fused_pub.publish(fused_odom)



    def HJacobian(self, x):
        return np.array([
            [1, 0, 0, 0, 0],
            [0, 1, 0, 0, 0], 
            [0, 0, 1, 0, 0]
        ])

    def Hx(self, x):
        return np.array([x[0], x[1], x[2]])

def main(args=None):
    rclpy.init(args=args)
    node = Fusion()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()