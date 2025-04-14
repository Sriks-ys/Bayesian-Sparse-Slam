import rclpy
from rclpy.node import Node
from messages.msg import LandmarkLandmarkConstraintList
from visualization_msgs.msg import Marker
from geometry_msgs.msg import Point

class LandmarkLandmarkVisualizationNode(Node):
    def __init__(self):
        super().__init__('LandmarkLandmarkVisualizationNode')

        self.subscription = self.create_subscription(
            LandmarkLandmarkConstraintList,
            '/Eu_landmarklandmark_cons',
            self.constraint_callback,
            10
        )

        self.publisher = self.create_publisher(
            Marker,
            '/Eu',
            10
        )

        self.landmark_positions = {}  

    def constraint_callback(self, msg):
        """ Updates visualization based on landmark constraints. """
        marker = Marker()
        marker.header = msg.header
        marker.ns = "landmark_landmark_constraints"
        marker.id = 0
        marker.type = Marker.LINE_LIST
        marker.action = Marker.ADD
        marker.scale.x = 0.05 
        marker.color.a = 1.0 
        marker.color.b = 1.0  

        sp_marker = Marker()
        sp_marker.header = msg.header
        sp_marker.id = 1
        sp_marker.type = Marker.SPHERE_LIST
        sp_marker.action = Marker.ADD
        sp_marker.scale.x = 0.1
        sp_marker.scale.y = 0.1
        sp_marker.scale.z = 0.1
        sp_marker.color.a = 1.0
        sp_marker.color.r = 1.0  # Red

        


        for constraint in msg.constraints:
            
            if constraint.landmark1_id not in self.landmark_positions or constraint.landmark2_id not in self.landmark_positions:
                continue  

            start_pos = self.landmark_positions[constraint.landmark1_id]
            end_pos = self.landmark_positions[constraint.landmark2_id]

            start = Point(x=start_pos[0], y=start_pos[1], z=0.0)
            end = Point(x=end_pos[0], y=end_pos[1], z=0.0)

            sp_marker.points.append(start)
            sp_marker.points.append(end)
            
            marker.points.append(start)
            marker.points.append(end)

        self.publisher.publish(marker)
        self.publisher.publish(sp_marker)

    def update_landmark_positions(self, landmark_msg):
        """ Updates landmark positions for visualization. """
        self.landmark_positions = {lm.landmark1_id: (lm.dx, lm.dy) for lm in landmark_msg.constraints}
        self.landmark_positions.update({lm.landmark2_id: (lm.dx, lm.dy) for lm in landmark_msg.constraints})

def main(args=None):
    rclpy.init(args=args)
    node = LandmarkLandmarkVisualizationNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
