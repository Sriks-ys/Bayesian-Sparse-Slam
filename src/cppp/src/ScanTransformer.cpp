#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <tf2_sensor_msgs/tf2_sensor_msgs.hpp>

class ScanTransformer : public rclcpp::Node {
public:
    ScanTransformer() : Node("scan_transformer"), tf_buffer_(this->get_clock()), tf_listener_(tf_buffer_) {
        scan_sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
            "/acc_filter_lid_frame", 10, std::bind(&ScanTransformer::scan_callback, this, std::placeholders::_1));
        transformed_scan_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/acc_filter", 10);
    }

private:
    void scan_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg) {
        geometry_msgs::msg::TransformStamped transform_stamped;
        try {
            transform_stamped = tf_buffer_.lookupTransform("map", msg->header.frame_id, msg->header.stamp, rclcpp::Duration::from_seconds(0.1));
        } catch (tf2::TransformException &ex) {
            RCLCPP_WARN(this->get_logger(), "Could not transform %s to map: %s", msg->header.frame_id.c_str(), ex.what());
            return;
        }

        sensor_msgs::msg::PointCloud2 transformed_cloud;
        tf2::doTransform(*msg, transformed_cloud, transform_stamped);
        transformed_cloud.header.frame_id = "map";
        transformed_cloud.header.stamp = this->now();
        transformed_scan_pub_->publish(transformed_cloud);
    }

    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr scan_sub_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr transformed_scan_pub_;
    tf2_ros::Buffer tf_buffer_;
    tf2_ros::TransformListener tf_listener_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ScanTransformer>());
    rclcpp::shutdown();
    return 0;
}
