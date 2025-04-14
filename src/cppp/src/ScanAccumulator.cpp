#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <tf2/utils.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/common/transforms.h>
#include <pcl_conversions/pcl_conversions.h>
#include <deque>
#include <Eigen/Geometry>
class ScanAccumulator : public rclcpp::Node {
public:
    ScanAccumulator() : Node("ScanAccumulator"), tf_buffer_(this->get_clock()), tf_listener_(tf_buffer_) {
        sparse_scan_sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
            "/sparse_scan", 10, std::bind(&ScanAccumulator::scan_callback, this, std::placeholders::_1));
        odom_sub_ = this->create_subscription<nav_msgs::msg::Odometry>(
            "/odom_fused", 10, std::bind(&ScanAccumulator::odom_callback, this, std::placeholders::_1));
        accumulated_scan_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/accumulated_scan", 10);
    }

private:
    struct ScanData {
        pcl::PointCloud<pcl::PointXYZ> cloud;
        geometry_msgs::msg::Pose pose;
    };

    void scan_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg) {
        if (last_pose_.position.x == 0 && last_pose_.position.y == 0) return;
        
        pcl::PointCloud<pcl::PointXYZ> cloud;
        pcl::fromROSMsg(*msg, cloud);
        scan_buffer_.push_back({cloud, last_pose_});

        if (scan_buffer_.size() > 100) {
            scan_buffer_.pop_front();
        }
        publish_accumulated_scan(msg);
    }

    void odom_callback(const nav_msgs::msg::Odometry::SharedPtr msg) {
        double current_yaw = tf2::getYaw(msg->pose.pose.orientation);
        double previous_yaw = tf2::getYaw(last_pose_.orientation);
    
        double yaw_diff = std::abs(current_yaw - previous_yaw);
        if (yaw_diff > 0.0001) {  
            scan_buffer_.clear(); 
        }
    
        last_pose_ = msg->pose.pose;  
    }
    

    void publish_accumulated_scan(const sensor_msgs::msg::PointCloud2::SharedPtr msg) {
        pcl::PointCloud<pcl::PointXYZ> merged_cloud;
    
        Eigen::Affine3f latest_pose_tf = poseToTransform(last_pose_);
    
        for (const auto &scan : scan_buffer_) {
            pcl::PointCloud<pcl::PointXYZ> transformed_cloud;
            
            
            Eigen::Affine3f scan_tf = poseToTransform(scan.pose);
            Eigen::Affine3f correction_tf = latest_pose_tf.inverse() * scan_tf;  
            
            pcl::transformPointCloud(scan.cloud, transformed_cloud, correction_tf);
            merged_cloud += transformed_cloud;
        }
    
        sensor_msgs::msg::PointCloud2 output;
        pcl::toROSMsg(merged_cloud, output);
        output.header.frame_id = msg->header.frame_id;  
        output.header.stamp = this->now();
        accumulated_scan_pub_->publish(output);
    }
    
    
    Eigen::Affine3f poseToTransform(const geometry_msgs::msg::Pose &pose) {
        return Eigen::Translation3f(pose.position.x, pose.position.y, 0.0f) *
               Eigen::AngleAxisf(tf2::getYaw(pose.orientation), Eigen::Vector3f::UnitZ());
    }
    

    void transform_scan(const pcl::PointCloud<pcl::PointXYZ> &input, const geometry_msgs::msg::Pose &pose, pcl::PointCloud<pcl::PointXYZ> &output) {
        Eigen::Affine3f transform = Eigen::Translation3f(pose.position.x, pose.position.y, 0.0f) *
                                    Eigen::AngleAxisf(tf2::getYaw(pose.orientation), Eigen::Vector3f::UnitZ());
        pcl::transformPointCloud(input, output, transform);
    }

    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr sparse_scan_sub_;
    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr accumulated_scan_pub_;
    std::deque<ScanData> scan_buffer_;
    geometry_msgs::msg::Pose last_pose_;
    tf2_ros::Buffer tf_buffer_;
    tf2_ros::TransformListener tf_listener_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ScanAccumulator>());
    rclcpp::shutdown();
    return 0;
}
