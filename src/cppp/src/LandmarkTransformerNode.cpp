#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <tf2/utils.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <Eigen/Geometry>
#include "messages/msg/line_segment_list.hpp"
#include "messages/msg/line_segment.hpp"

class LandmarkTransformerNode : public rclcpp::Node {
public:
    LandmarkTransformerNode() : Node("LandmarkTransformerNode"), tf_buffer_(this->get_clock()), tf_listener_(tf_buffer_) {
        line_segment_sub_ = this->create_subscription<messages::msg::LineSegmentList>(
            "/extracted_lines", 10, std::bind(&LandmarkTransformerNode::line_segment_callback, this, std::placeholders::_1));

        odom_sub_ = this->create_subscription<nav_msgs::msg::Odometry>(
            "/odom_fused", 10, std::bind(&LandmarkTransformerNode::odom_callback, this, std::placeholders::_1));

        transformed_line_pub_ = this->create_publisher<messages::msg::LineSegmentList>("/transformed_lines", 10);
        }

private:
    rclcpp::Subscription<messages::msg::LineSegmentList>::SharedPtr line_segment_sub_;
    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub_;
    rclcpp::Publisher<messages::msg::LineSegmentList>::SharedPtr transformed_line_pub_;
    
    tf2_ros::Buffer tf_buffer_;
    tf2_ros::TransformListener tf_listener_;
    geometry_msgs::msg::Pose last_pose_;

    std::vector<messages::msg::LineSegment> persistent_landmarks_;

    void line_segment_callback(const messages::msg::LineSegmentList::SharedPtr msg) {
        if (last_pose_.position.x == 0 && last_pose_.position.y == 0) {
            RCLCPP_WARN(this->get_logger(), "Waiting for valid odometry before transforming line segments.");
            return;
        }

        messages::msg::LineSegmentList transformed_msg;
        transformed_msg.header = msg->header;
        transformed_msg.header.frame_id = "odom"; 

        Eigen::Affine3f transform = poseToTransform(last_pose_);

        for (const auto &segment : msg->segments) {
            messages::msg::LineSegment transformed_segment = segment;

            Eigen::Vector3f start(segment.start.x, segment.start.y, 0.0f);
            Eigen::Vector3f end(segment.end.x, segment.end.y, 0.0f);

            start = transform * start;
            end = transform * end;

            transformed_segment.start.x = start.x();
            transformed_segment.start.y = start.y();
            transformed_segment.end.x = end.x();
            transformed_segment.end.y = end.y();

            transformed_msg.segments.push_back(transformed_segment);
        }

        transformed_line_pub_->publish(transformed_msg);

    }


    void odom_callback(const nav_msgs::msg::Odometry::SharedPtr msg) {
        last_pose_ = msg->pose.pose;
    }

    Eigen::Affine3f poseToTransform(const geometry_msgs::msg::Pose &pose) {
        return Eigen::Translation3f(pose.position.x, pose.position.y, 0.0f) *
               Eigen::AngleAxisf(tf2::getYaw(pose.orientation), Eigen::Vector3f::UnitZ());
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<LandmarkTransformerNode>());
    rclcpp::shutdown();
    return 0;
}
