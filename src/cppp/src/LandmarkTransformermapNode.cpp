#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <tf2/utils.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <Eigen/Geometry>
#include "messages/msg/line_segment_list.hpp"
#include "messages/msg/line_segment.hpp"

class LandmarkTransformermapNode : public rclcpp::Node {
public:
    LandmarkTransformermapNode() 
        : Node("LandmarkTransformermapNode"), tf_buffer_(this->get_clock()), tf_listener_(tf_buffer_) {

        line_segment_sub_ = this->create_subscription<messages::msg::LineSegmentList>(
            "/extracted_lines", 10, 
            std::bind(&LandmarkTransformermapNode::line_segment_callback, this, std::placeholders::_1));

        transformed_line_pub_ = this->create_publisher<messages::msg::LineSegmentList>(
            "/transformed_lines", 10);
    }

private:
    rclcpp::Subscription<messages::msg::LineSegmentList>::SharedPtr line_segment_sub_;
    rclcpp::Publisher<messages::msg::LineSegmentList>::SharedPtr transformed_line_pub_;
    
    tf2_ros::Buffer tf_buffer_;
    tf2_ros::TransformListener tf_listener_;
    
    void line_segment_callback(const messages::msg::LineSegmentList::SharedPtr msg) {
        geometry_msgs::msg::TransformStamped map_to_sensor_tf;

        try {
            
            map_to_sensor_tf = tf_buffer_.lookupTransform("map", msg->header.frame_id, tf2::TimePointZero);
        } catch (tf2::TransformException &ex) {
           
            return;
        }

      
        Eigen::Affine3f map_transform = tfToEigen(map_to_sensor_tf);

        messages::msg::LineSegmentList transformed_msg;
        transformed_msg.header = msg->header;
        transformed_msg.header.frame_id = "map"; 

        for (const auto &segment : msg->segments) {
            messages::msg::LineSegment transformed_segment = segment;

            Eigen::Vector3f start(segment.start.x, segment.start.y, 0.0f);
            Eigen::Vector3f end(segment.end.x, segment.end.y, 0.0f);

            start = map_transform * start;
            end = map_transform * end;

            transformed_segment.start.x = start.x();
            transformed_segment.start.y = start.y();
            transformed_segment.end.x = end.x();
            transformed_segment.end.y = end.y();

            transformed_msg.segments.push_back(transformed_segment);
        }

        transformed_line_pub_->publish(transformed_msg);
    }

    Eigen::Affine3f tfToEigen(const geometry_msgs::msg::TransformStamped &transformStamped) {
        Eigen::Translation3f translation(
            transformStamped.transform.translation.x,
            transformStamped.transform.translation.y,
            transformStamped.transform.translation.z);

        Eigen::Quaternionf rotation(
            transformStamped.transform.rotation.w,
            transformStamped.transform.rotation.x,
            transformStamped.transform.rotation.y,
            transformStamped.transform.rotation.z);

        return translation * rotation;
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<LandmarkTransformermapNode>());
    rclcpp::shutdown();
    return 0;
}
