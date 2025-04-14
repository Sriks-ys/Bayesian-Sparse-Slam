#include <rclcpp/rclcpp.hpp>
#include <messages/msg/pose_graph.hpp>
#include <messages/msg/landmark_landmark_constraint_list.hpp>
#include <messages/msg/pose_graph.hpp>
#include <messages/msg/line_segment_list.hpp>
#include <geometry_msgs/msg/point.hpp>

#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/nonlinear/Values.h>
#include <gtsam/inference/Symbol.h>
#include <gtsam/slam/BetweenFactor.h>
#include <gtsam/slam/PriorFactor.h>
#include <gtsam/geometry/Pose2.h>
#include <gtsam/geometry/Point2.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/Marginals.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/linear/NoiseModel.h>
#include <gtsam/slam/BearingRangeFactor.h>



using std::placeholders::_1;
using namespace messages::msg;
using gtsam::symbol_shorthand::X;
using gtsam::symbol_shorthand::L;

class PoseGraphOptimizer : public rclcpp::Node {
public:
    PoseGraphOptimizer() : Node("pose_graph_optimizer") {
        pose_graph_sub_ = this->create_subscription<PoseGraph>(
            "/pose_graph", 10, std::bind(&PoseGraphOptimizer::poseGraphCallback, this, _1));
        landmark_sub_ = this->create_subscription<LineSegmentList>(
            "/global_landmarks", 10, std::bind(&PoseGraphOptimizer::landmarkCallback, this, _1));
        lm_lm_sub_ = this->create_subscription<LandmarkLandmarkConstraintList>(
            "/bayes_lm_lm", 10, std::bind(&PoseGraphOptimizer::landmarkLandmarkCallback, this, _1));

        pose_graph_pub_ = this->create_publisher<PoseGraph>("/optimized_posegraph", 10);
        landmark_pub_ = this->create_publisher<LineSegmentList>("/optimized_landmarks", 10);
    };

private:
    rclcpp::Subscription<PoseGraph>::SharedPtr pose_graph_sub_;
    rclcpp::Subscription<LineSegmentList>::SharedPtr landmark_sub_;
    rclcpp::Subscription<LandmarkLandmarkConstraintList>::SharedPtr lm_lm_sub_;

    rclcpp::Publisher<PoseGraph>::SharedPtr pose_graph_pub_;
    rclcpp::Publisher<LineSegmentList>::SharedPtr landmark_pub_;
    std::map<int, std::vector<int>> landmark_to_poses;
    std::set<std::pair<int, int>> added_loops;



    std::map<int32_t, messages::msg::LineSegment> landmark_map_;
    std::map<int32_t, gtsam::Matrix> landmark_cov_;
    LandmarkLandmarkConstraintList::SharedPtr lm_lm_msg_;

    void landmarkCallback(LineSegmentList::SharedPtr msg) {
        for (size_t i = 0; i < msg->segments.size(); ++i) {
            const auto& seg = msg->segments[i];
            landmark_map_[i] = seg;
        }
    };

    void landmarkLandmarkCallback(LandmarkLandmarkConstraintList::SharedPtr msg) {
        lm_lm_msg_ = msg;
    };

    bool isValidCovariance(const gtsam::Matrix& cov) {
        Eigen::SelfAdjointEigenSolver<gtsam::Matrix> es(cov);
        return cov.allFinite() && es.eigenvalues().minCoeff() > 1e-9;
    };

    void poseGraphCallback(PoseGraph::SharedPtr msg) {
        gtsam::NonlinearFactorGraph graph;
        gtsam::Values initial;

        if (msg->nodes.size() < 2) {
            return;
        }

        for (const auto& lm : msg->landmark_constraints) {
            landmark_to_poses[lm.landmark_id].push_back(lm.pose_id);
        }

        RCLCPP_INFO(this->get_logger(), "Received pose graph with %zu nodes, %zu pose constraints, %zu landmark constraints.",
                    msg->nodes.size(), msg->pose_constraints.size(), msg->landmark_constraints.size());
    
        if (lm_lm_msg_) {
            RCLCPP_INFO(this->get_logger(), "Received %zu landmark-landmark constraints.", lm_lm_msg_->constraints.size());
        } else {
            RCLCPP_INFO(this->get_logger(), "No landmark-landmark constraints received yet.");
        }
    
        // Add pose nodes
        for (const auto& node : msg->nodes) {
            gtsam::Pose2 pose(node.x, node.y, node.theta);
            RCLCPP_DEBUG(this->get_logger(), "Inserting initial pose X%d = (%.3f, %.3f, %.3f)", node.id, node.x, node.y, node.theta);
            initial.insert(X(node.id), pose);
    
            if (node.id == 0) {
                gtsam::Matrix cov = gtsam::Matrix::Identity(3, 3) * 1e-6;
                if (!isValidCovariance(cov)) {
                    RCLCPP_WARN(this->get_logger(), "Invalid prior covariance for pose 0.");
                    continue;
                }
                auto prior = gtsam::noiseModel::Gaussian::Covariance(cov);
                graph.add(gtsam::PriorFactor<gtsam::Pose2>(X(0), pose, prior));
            }
        }

        for (const auto& [landmark_id, poses] : landmark_to_poses) {
            for (size_t i = 0; i < poses.size(); ++i) {
                for (size_t j = i + 1; j < poses.size(); ++j) {
                    int id1 = poses[i];
                    int id2 = poses[j];
                    if (abs(id1 - id2) <= 1) continue;  // skip consecutive (odometry) edges
        
                    // Avoid duplicate loop closures
                    auto key = std::minmax(id1, id2);
                    if (added_loops.count(key)) continue;
                    added_loops.insert(key);
        
                    if (!initial.exists(X(id1)) || !initial.exists(X(id2))) continue;
        
                    auto pose1 = initial.at<gtsam::Pose2>(X(id1));
                    auto pose2 = initial.at<gtsam::Pose2>(X(id2));
                    gtsam::Pose2 delta = pose1.between(pose2);
        
                    // Use a loose covariance to let optimizer refine it
                    gtsam::Matrix loop_cov = gtsam::Matrix::Identity(3, 3) * 0.1;
                    auto model = gtsam::noiseModel::Gaussian::Covariance(loop_cov);
        
                    graph.add(gtsam::BetweenFactor<gtsam::Pose2>(X(id1), X(id2), delta, model));
        
                    RCLCPP_INFO(this->get_logger(),
                                "Added loop closure between X%d and X%d via shared landmark L%d",
                                id1, id2, landmark_id);
                }
            }
        }
    
        // Pose-pose constraints
        for (const auto& pc : msg->pose_constraints) {
            gtsam::Pose2 delta(pc.dx, pc.dy, pc.dtheta);
            gtsam::Matrix cov(3, 3);
            for (int i = 0; i < 9; ++i) cov(i / 3, i % 3) = pc.covariance[i];
    
            RCLCPP_DEBUG(this->get_logger(), "Pose constraint from X%d to X%d with delta (%.3f, %.3f, %.3f)",
                         pc.pose1_id, pc.pose2_id, pc.dx, pc.dy, pc.dtheta);
            RCLCPP_DEBUG(this->get_logger(), "Covariance:\n%.3f %.3f %.3f\n%.3f %.3f %.3f\n%.3f %.3f %.3f",
                         cov(0,0), cov(0,1), cov(0,2),
                         cov(1,0), cov(1,1), cov(1,2),
                         cov(2,0), cov(2,1), cov(2,2));
    
            if (!isValidCovariance(cov)) {
                RCLCPP_WARN(this->get_logger(), "Invalid covariance in pose constraint X%d -> X%d", pc.pose1_id, pc.pose2_id);
                continue;
            }
    
            auto model = gtsam::noiseModel::Gaussian::Covariance(cov);
            graph.add(gtsam::BetweenFactor<gtsam::Pose2>(X(pc.pose1_id), X(pc.pose2_id), delta, model));
        }
    
        // Pose-landmark constraints
        for (const auto& lm : msg->landmark_constraints) {
            if (landmark_map_.count(lm.landmark_id) == 0) {
                RCLCPP_WARN(this->get_logger(), "Landmark ID %d not found in map. Skipping.", lm.landmark_id);
                continue;
            }
    
            const auto& pose_node = *std::find_if(msg->nodes.begin(), msg->nodes.end(),
                                                  [&](const auto& n) { return n.id == lm.pose_id; });
    
            if (!std::isfinite(pose_node.theta) || !std::isfinite(lm.alpha)) {
                RCLCPP_WARN(this->get_logger(), "Skipping invalid angle values in pose-landmark constraint (pose_id=%d)", lm.pose_id);
                continue;
            }
    
            float x = pose_node.x + lm.rho * cos(pose_node.theta + lm.alpha);
            float y = pose_node.y + lm.rho * sin(pose_node.theta + lm.alpha);
            gtsam::Point2 observed(x, y);
    
            RCLCPP_DEBUG(this->get_logger(), "Pose-landmark: Pose X%d observed L%d at (%.3f, %.3f)", lm.pose_id, lm.landmark_id, x, y);
    
            gtsam::Matrix cov(2, 2);
            cov << lm.covariance[0], lm.covariance[1],
                   lm.covariance[2], lm.covariance[3];
    
            if (!isValidCovariance(cov)) {
                RCLCPP_WARN(this->get_logger(), "Invalid landmark covariance for L%d. Skipping.", lm.landmark_id);
                continue;
            }
    
            auto model = gtsam::noiseModel::Gaussian::Covariance(cov);
            auto pose_key = X(lm.pose_id);
            auto landmark_key = L(lm.landmark_id);

            gtsam::Pose2 pose_est = initial.at<gtsam::Pose2>(pose_key);
            gtsam::Point2 landmark_rel = observed - gtsam::Point2(pose_est.x(), pose_est.y());

            auto br_model = gtsam::noiseModel::Diagonal::Sigmas((gtsam::Vector(2) << std::sqrt(lm.covariance[0]), std::sqrt(lm.covariance[3])).finished());
            gtsam::BearingRangeFactor<gtsam::Pose2, gtsam::Point2> br_factor(pose_key, landmark_key,
                gtsam::Rot2(lm.alpha), lm.rho, br_model);
            graph.add(br_factor);


    
            if (!initial.exists(L(lm.landmark_id))) {
                initial.insert(L(lm.landmark_id), observed);
                RCLCPP_DEBUG(this->get_logger(), "Inserted initial landmark L%d = (%.3f, %.3f)", lm.landmark_id, x, y);
            }
        }
    
        // Landmark-landmark constraints
        if (lm_lm_msg_) {
            for (const auto& constraint : lm_lm_msg_->constraints) {
                int id1 = constraint.landmark1_id;
                int id2 = constraint.landmark2_id;
    
                gtsam::Matrix cov(2, 2);
                cov << constraint.covariance[0], constraint.covariance[1],
                       constraint.covariance[2], constraint.covariance[3];
    
                RCLCPP_DEBUG(this->get_logger(), "Landmark-landmark: L%d <-> L%d, dx=%.3f dy=%.3f", id1, id2, constraint.dx, constraint.dy);
    
                if (!isValidCovariance(cov)) {
                    RCLCPP_WARN(this->get_logger(), "Invalid covariance in landmark-landmark constraint L%d <-> L%d", id1, id2);
                    continue;
                }
    
                auto model = gtsam::noiseModel::Gaussian::Covariance(cov);
                gtsam::Point2 diff(constraint.dx, constraint.dy);
                graph.add(gtsam::BetweenFactor<gtsam::Point2>(L(id1), L(id2), diff, model));
    
                auto guessFromObservation = [&](int landmark_id) -> std::optional<gtsam::Point2> {
                    for (const auto& obs : msg->landmark_constraints) {
                        if (obs.landmark_id == landmark_id) {
                            auto it = std::find_if(msg->nodes.begin(), msg->nodes.end(),
                                                   [&](const auto& n) { return n.id == obs.pose_id; });
                            if (it != msg->nodes.end()) {
                                float x = it->x + obs.rho * cos(it->theta + obs.alpha);
                                float y = it->y + obs.rho * sin(it->theta + obs.alpha);
                                return gtsam::Point2(x, y);
                            }
                        }
                    }
                    return std::nullopt;
                };
                
                if (!initial.exists(L(id1))) {
                    auto guess = guessFromObservation(id1).value_or(gtsam::Point2(0.0, 0.0));
                    initial.insert(L(id1), guess);
                    RCLCPP_DEBUG(this->get_logger(), "Initial guess for L%d = (%.3f, %.3f)", id1, guess.x(), guess.y());
                }
                if (!initial.exists(L(id2))) {
                    auto guess = guessFromObservation(id2).value_or(gtsam::Point2(constraint.dx, constraint.dy));
                    initial.insert(L(id2), guess);
                    RCLCPP_DEBUG(this->get_logger(), "Initial guess for L%d = (%.3f, %.3f)", id2, guess.x(), guess.y());
                }                
            }
        }
    
        RCLCPP_INFO(this->get_logger(), "Constructed factor graph with %zu factors and %zu initial values.",
                    graph.size(), initial.size());
    
        double initialError = graph.error(initial);
        RCLCPP_INFO(this->get_logger(), "Initial total error: %.6f", initialError);
    
        gtsam::LevenbergMarquardtParams params;
        params.setVerbosityLM("SUMMARY");
        params.setMaxIterations(100);
        gtsam::LevenbergMarquardtOptimizer optimizer(graph, initial, params);
        gtsam::Values result = optimizer.optimize();
        double finalError = graph.error(result);

        gtsam::Marginals marginals(graph, result);
    
        RCLCPP_INFO(this->get_logger(), "Optimization complete.");
        RCLCPP_INFO(this->get_logger(), "Final total error: %.6f", finalError);
        RCLCPP_INFO(this->get_logger(), "Total error reduction: %.6f", initialError - finalError);
    
        // Publish optimized pose graph
        PoseGraph out_msg;
        out_msg.header = msg->header;
        for (const auto& node : msg->nodes) {
            PoseNode opt;
            opt.id = node.id;
            auto est = result.at<gtsam::Pose2>(X(node.id));
            opt.x = est.x();
            opt.y = est.y();
            opt.theta = est.theta();
            out_msg.nodes.push_back(opt);
        }
        out_msg.pose_constraints = msg->pose_constraints;
        out_msg.landmark_constraints = msg->landmark_constraints;
        pose_graph_pub_->publish(out_msg);

        LineSegmentList landmark_out;
        landmark_out.header = msg->header;

        for (const auto& [id, seg] : landmark_map_) {
            if (!result.exists(L(id))) continue;

            gtsam::Point2 pt = result.at<gtsam::Point2>(L(id));

            LineSegment optimized;
            optimized.rho = seg.rho;
            optimized.alpha = seg.alpha;
            float dx = seg.end.x - seg.start.x;
            float dy = seg.end.y - seg.start.y;
            try {
                gtsam::Matrix full_cov = marginals.marginalCovariance(L(id));
                gtsam::Matrix cov2x2 = full_cov.block<2,2>(0,0);
            
                optimized.covariance[0] = cov2x2(0, 0);
                optimized.covariance[1] = cov2x2(0, 1);
                optimized.covariance[2] = cov2x2(1, 0);
                optimized.covariance[3] = cov2x2(1, 1);
            } catch (const std::exception& e) {
                RCLCPP_WARN(this->get_logger(), "Failed to compute covariance for L%d: %s", id, e.what());
                optimized.covariance = seg.covariance; // fallback
            }
            geometry_msgs::msg::Point center;
            center.x = pt.x();
            center.y = pt.y();
            center.z = 0.0;
            geometry_msgs::msg::Point new_start, new_end;
            new_start.x = center.x - dx / 2.0;
            new_start.y = center.y - dy / 2.0;
            new_end.x = center.x + dx / 2.0;
            new_end.y = center.y + dy / 2.0;
            new_start.z = new_end.z = 0.0;

            optimized.start = new_start;
            optimized.end = new_end;

            landmark_out.segments.push_back(optimized);
        }
        landmark_pub_->publish(landmark_out);

    };    
};
int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PoseGraphOptimizer>());
    rclcpp::shutdown();
    return 0;
}
