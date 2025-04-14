import rclpy
import numpy as np
from rclpy.node import Node
from collections import defaultdict
from messages.msg import PoseGraph, LandmarkLandmarkConstraint, LandmarkLandmarkConstraintList

class BayesianLandmarkConstraintNode(Node):
    def __init__(self):
        super().__init__('bayesian_landmark_constraint_node')
        self.pose_graph_sub = self.create_subscription(
            PoseGraph, '/pose_graph', self.pose_graph_callback, 10)
        self.constraint_pub = self.create_publisher(
            LandmarkLandmarkConstraintList, '/bayes_lm_lm', 10)
        
        self.max_distance = 3.5

    def pose_graph_callback(self, msg):
        """Processes the pose graph to compute fused landmark-landmark constraints."""
        pose_covs = {node.id: np.array(node.covariance).reshape(3, 3) for node in msg.nodes}
        pose_states = {node.id: (node.x, node.y, node.theta) for node in msg.nodes}

        # Store multiple observations per landmark
        landmark_observations = defaultdict(list)

        for constraint in msg.landmark_constraints:
            pose_id = constraint.pose_id
            landmark_id = constraint.landmark_id
            rho, alpha = constraint.rho, constraint.alpha
            lm_cov = np.array(constraint.covariance).reshape(2, 2)

            if pose_id not in pose_covs or pose_id not in pose_states:
                continue

            pose_x, pose_y, pose_theta = pose_states[pose_id]
            pose_cov = pose_covs[pose_id]

            # Compute Jacobians
            J_p, J_l = self.compute_jacobians(pose_theta, rho, alpha)

            # Propagate covariance
            Sigma_ll = J_p @ pose_cov @ J_p.T + J_l @ lm_cov @ J_l.T

            # Compute landmark position in map frame
            x_lm = pose_x + rho * np.cos(pose_theta + alpha)
            y_lm = pose_y + rho * np.sin(pose_theta + alpha)

            # Store the observation
            landmark_observations[landmark_id].append((x_lm, y_lm, Sigma_ll))

        # Fuse landmark observations
        landmark_positions = {}
        landmark_covs = {}

        for lm_id, obs_list in landmark_observations.items():
            fused_x, fused_y, fused_cov = self.fuse_observations(obs_list)
            landmark_positions[lm_id] = (fused_x, fused_y)
            landmark_covs[lm_id] = fused_cov

        # Create landmark-landmark constraints
        constraints = []
        landmark_ids = sorted(landmark_positions.keys())

        for i in range(len(landmark_ids)):
            for j in range(i + 1, len(landmark_ids)):
                lm1 = landmark_ids[i]
                lm2 = landmark_ids[j]

                x1, y1 = landmark_positions[lm1]
                x2, y2 = landmark_positions[lm2]

                dx = x2 - x1
                dy = y2 - y1

                # Add this:
                if dx**2 + dy**2 > self.max_distance**2:
                    continue




                Sigma_lm1 = landmark_covs[lm1]
                Sigma_lm2 = landmark_covs[lm2]

                Sigma_ll = Sigma_lm1 + Sigma_lm2  # Uncertainty of relative constraint

                constraint_msg = LandmarkLandmarkConstraint()
                constraint_msg.landmark1_id = lm1
                constraint_msg.landmark2_id = lm2
                constraint_msg.dx = dx
                constraint_msg.dy = dy
                constraint_msg.covariance = Sigma_ll.flatten().tolist()

                constraints.append(constraint_msg)

        # Publish constraints
        constraint_list_msg = LandmarkLandmarkConstraintList()
        constraint_list_msg.constraints = constraints
        self.constraint_pub.publish(constraint_list_msg)

    def compute_jacobians(self, theta, rho, alpha):
        """ Computes Jacobians J_p and J_l for uncertainty propagation. """
        theta_lm = theta + alpha
        J_p = np.array([
            [1, 0, -rho * np.sin(theta_lm)],
            [0, 1, rho * np.cos(theta_lm)]
        ])
        J_l = np.array([
            [np.cos(theta_lm), -rho * np.sin(theta_lm)],
            [np.sin(theta_lm), rho * np.cos(theta_lm)]
        ])
        return J_p, J_l

    def fuse_observations(self, obs_list):
        """Fuse multiple landmark observations using information filter (Gaussian fusion)."""
        Omega_total = np.zeros((2, 2))
        xi_total = np.zeros(2)

        for (x, y, cov) in obs_list:
            try:
                Omega = np.linalg.inv(cov)
            except np.linalg.LinAlgError:
                self.get_logger().warn("Singular covariance encountered, skipping.")
                continue
            xi = Omega @ np.array([x, y])

            Omega_total += Omega
            xi_total += xi

        if np.linalg.det(Omega_total) < 1e-6:
            self.get_logger().warn("Total information matrix nearly singular, returning average.")
            # Fall back to mean
            xy = np.mean(np.array([[x, y] for (x, y, _) in obs_list]), axis=0)
            cov = np.eye(2) * 1e6  # large uncertainty
            return xy[0], xy[1], cov

        mu = np.linalg.inv(Omega_total) @ xi_total
        cov = np.linalg.inv(Omega_total)
        return mu[0], mu[1], cov

def main():
    rclpy.init()
    node = BayesianLandmarkConstraintNode()
    rclpy.spin(node)
    rclpy.shutdown()