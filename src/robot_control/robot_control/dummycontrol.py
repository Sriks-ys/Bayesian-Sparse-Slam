#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
from rclpy.time import Time
from rosgraph_msgs.msg import Clock  # To read /clock topic

class DummyControl(Node):
    def __init__(self):
        super().__init__('dummycontrol')
        self.publisher = self.create_publisher(Twist, '/dummy_cmd', 10)
        self.clock_sub = self.create_subscription(Clock, '/clock', self.clock_callback, 10)
        
        self.state = 0
        self.sim_time = 0.0  
        self.start_time = None  

        
        self.state_durations = {
            0: 8.5,  
            1: 2.895, 
            2: 7.6,  
            3: 3.36,  
            4: 8.5, 
            5: 3.1,
            6: 7.4,
            7: 3.37  
        }

        
        while self.sim_time == 0.0: 
            rclpy.spin_once(self)

        self.start_time = self.sim_time
        self.control_loop()

    def clock_callback(self, msg):
        """Updates the latest simulation time."""
        self.sim_time = msg.clock.sec + msg.clock.nanosec * 1e-9

    def control_loop(self):
        """Main control loop, switches states based on simulation time."""
        while rclpy.ok():
            rclpy.spin_once(self)  

            if self.start_time is None:  
                continue

            elapsed_time = self.sim_time - self.start_time
          

            if elapsed_time >= self.state_durations[self.state]:  
                self.state = (self.state + 1) % 8  
                self.start_time = self.sim_time  
               

           
            t = Twist()
            if self.state == 0:  
                t.linear.x = 0.5
                
            elif self.state == 1:  
                t.angular.z = 0.5
               
            elif self.state == 2: 
                t.linear.x = 0.5
               
            elif self.state == 3:  
                t.linear.x = 0.0
                t.angular.z = 0.5
               
            elif self.state == 4:  
                t.linear.x = 0.5
                t.angular.z = 0.0
               
            elif self.state == 5: 
                t.linear.x = 0.0
                t.angular.z = 0.5
                
            elif self.state == 6:
                t._linear.x = 0.5
                t._angular.z = 0.0 
               
            elif self.state == 7: 
                t.linear.x = 0.0
                t.angular.z = 0.5
               

            self.publisher.publish(t)

def main(args=None):
    rclpy.init(args=args)
    node = DummyControl()
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
