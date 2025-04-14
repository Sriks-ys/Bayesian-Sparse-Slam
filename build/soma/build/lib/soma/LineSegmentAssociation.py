import rclpy
from rclpy.node import Node
from messages.msg import LineSegmentList, LineSegment
import numpy as np

class LineSegmentAssociation(Node):
    def __init__(self):
        super().__init__("linesegmentassociation")
        
        # Subscribers
        self.landmark_sub = self.create_subscription(LineSegmentList, "/persistent_landmarks", self.landmark_callback, 10)
        self.observed_lines_sub = self.create_subscription(LineSegmentList, "/transformed_lines", self.observed_lines_callback, 10)
        
        # Publisher
        self.associated_landmarks_pub = self.create_publisher(LineSegmentList, "/associated_landmarks", 10)

        # Store landmarks
        self.landmarks = []

    def landmark_callback(self, msg):
        """ Store the existing landmarks when received """
        self.landmarks = msg.segments

    def observed_lines_callback(self, msg):
        if not self.landmarks:
            #self.get_logger().warn("No landmarks available for association!")
            return

        associated_lines = LineSegmentList()
        associated_lines.header = msg.header

        for observed in msg.segments:
            best_match, min_error = None, float("inf")

            for landmark in self.landmarks:
                error = self.compute_projection_error(observed, landmark)
                if self.check_line_projection_error(observed, landmark) and self.check_endpoint_overlap(observed, landmark):
                    if error < min_error:
                        best_match, min_error = landmark, error

            if best_match:
                associated_lines.segments.append(best_match)
                
            else:
                
                self.landmarks.append(observed)  
                associated_lines.segments.append(observed)
            

        self.associated_landmarks_pub.publish(associated_lines)

    def check_line_projection_error(self, observed, landmark, epsilon=5.0):  
        """ Compute projection error using equation (5) """
        p1, p2 = np.array([observed.start.x, observed.start.y]), np.array([observed.end.x, observed.end.y])
        a = np.array([landmark.rho * np.cos(landmark.alpha), landmark.rho * np.sin(landmark.alpha)])
        d = np.array([-np.sin(landmark.alpha), np.cos(landmark.alpha)])

        t1, t2 = np.dot((p1 - a), d), np.dot((p2 - a), d)
        projection_error = np.linalg.norm(p1 - (a + t1 * d)) + np.linalg.norm(p2 - (a + t2 * d))
        return projection_error <= epsilon

    def check_endpoint_overlap(self, observed, landmark):
        """ Check if projected endpoints overlap using equation (8) """
        p1, p2 = np.array([observed.start.x, observed.start.y]), np.array([observed.end.x, observed.end.y])
        a = np.array([landmark.rho * np.cos(landmark.alpha), landmark.rho * np.sin(landmark.alpha)])
        d = np.array([-np.sin(landmark.alpha), np.cos(landmark.alpha)])

        t1, t2 = np.dot((p1 - a), d), np.dot((p2 - a), d)
        s1, s2 = np.dot((np.array([landmark.start.x, landmark.start.y]) - a), d), np.dot((np.array([landmark.end.x, landmark.end.y]) - a), d)

        return not (max(s1, s2) < min(t1, t2) or max(t1, t2) < min(s1, s2))

    def compute_projection_error(self, observed, landmark):
        p1, p2 = np.array([observed.start.x, observed.start.y]), np.array([observed.end.x, observed.end.y])
        a = np.array([landmark.rho * np.cos(landmark.alpha), landmark.rho * np.sin(landmark.alpha)])
        d = np.array([-np.sin(landmark.alpha), np.cos(landmark.alpha)])

        t1, t2 = np.dot((p1 - a), d), np.dot((p2 - a), d)
        
       
        error1 = np.linalg.norm(p1 - (a + t1 * d))
        error2 = np.linalg.norm(p2 - (a + t2 * d))
        
        return max(error1, error2) 


def main(args=None):
    rclpy.init(args=args)
    node = LineSegmentAssociation()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()
