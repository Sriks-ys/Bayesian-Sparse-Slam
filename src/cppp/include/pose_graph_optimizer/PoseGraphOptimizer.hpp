#ifndef POSE_GRAPH_OPTIMIZER_HPP
#define POSE_GRAPH_OPTIMIZER_HPP

#include <rclcpp/rclcpp.hpp>
#include <ceres/ceres.h>
#include <geometry_msgs/msg/point.hpp>
#include <messages/msg/pose_graph.hpp>
#include <messages/msg/line_segment_list.hpp>
#include <messages/msg/pose_constraint.hpp>
#include <messages/msg/landmark_constraint.hpp>

struct PoseGraphOptimizer : public rclcpp::Node {
    PoseGraphOptimizer();

private:
    void poseGraphCallback(const messages::msg::PoseGraph::SharedPtr msg);
    void landmarkCallback(const messages::msg::LineSegmentList::SharedPtr msg);
    void optimize();
    void publishOptimizedLandmarks();

    rclcpp::Subscription<messages::msg::PoseGraph>::SharedPtr pose_graph_sub_;
    rclcpp::Subscription<messages::msg::LineSegmentList>::SharedPtr landmarks_sub_;
    rclcpp::Publisher<messages::msg::LineSegmentList>::SharedPtr landmarks_pub_;

    std::unordered_map<int, Eigen::Vector3d> pose_estimates_; // ID → (x, y, theta)
    std::vector<messages::msg::LineSegment> landmarks_;
};

#endif // POSE_GRAPH_OPTIMIZER_HPP
