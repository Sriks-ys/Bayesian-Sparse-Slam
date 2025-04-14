#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <geometry_msgs/msg/point.hpp>
#include "messages/msg/line_segment.hpp"
#include "messages/msg/line_segment_list.hpp"
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <vector>
#include <cmath>
#include <limits>

using std::placeholders::_1;

class IncrementalLineFittingNode : public rclcpp::Node {
public:
    IncrementalLineFittingNode() : Node("IncrementalLineFittingNode") {
        sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
            "/acc_filter", 10, std::bind(&IncrementalLineFittingNode::scanCallback, this, _1));
        pub_ = this->create_publisher<messages::msg::LineSegmentList>("/extracted_lines", 10);
        odom_sub_ = this->create_subscription<nav_msgs::msg::Odometry>(
            "/odom_fused", 10, std::bind(&IncrementalLineFittingNode::odomCallback, this, _1));
        RCLCPP_INFO(this->get_logger(), "Incremental Line Fitting Node initialized.");
    }

private:
    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr sub_;
    rclcpp::Publisher<messages::msg::LineSegmentList>::SharedPtr pub_;
    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub_;

    double angular_velocity_threshold_ = 0.2;
    double current_angular_velocity_ = 0.0;
    double distance_threshold_ = 0.5;
    double max_fitting_error_ = 0.01;
    double min_segment_length_ = 0.7;
    double max_angle_difference_ = 1.0 * M_PI / 180.0;  // 10 degrees

    struct Point2D {
        double x, y;
    };

    void odomCallback(const nav_msgs::msg::Odometry::SharedPtr msg) {
        current_angular_velocity_ = std::abs(msg->twist.twist.angular.z);
    }

    void scanCallback(const sensor_msgs::msg::PointCloud2::SharedPtr msg) {
        double dynamic_threshold = angular_velocity_threshold_;
        if (current_angular_velocity_ > 0.1) {
            dynamic_threshold *= 1.5;
        }
        if (current_angular_velocity_ > dynamic_threshold) {
            return;
        }

        pcl::PointCloud<pcl::PointXYZ> pcl_cloud;
        pcl::fromROSMsg(*msg, pcl_cloud);
        std::vector<Point2D> points;
        for (const auto& p : pcl_cloud.points) {
            points.push_back({p.x, p.y});
        }

        auto line_segments = regionGrowingLineFitting(points);
        publishLines(line_segments, msg->header);
    }

    std::vector<std::pair<Point2D, Point2D>> regionGrowingLineFitting(const std::vector<Point2D>& points) {
        std::vector<std::pair<Point2D, Point2D>> line_segments;
        if (points.size() < 2) return line_segments;

        std::vector<bool> used(points.size(), false);
        for (size_t i = 0; i < points.size(); ++i) {
            if (used[i]) continue;

            std::vector<Point2D> segment_points = {points[i]};
            used[i] = true;

            for (size_t j = i + 1; j < points.size(); ++j) {
                if (used[j]) continue;

                if (std::hypot(points[j].x - segment_points.back().x, points[j].y - segment_points.back().y) < distance_threshold_) {
                    if (segment_points.size() >= 3) {
                        double avg_angle = atan2(segment_points.back().y - segment_points.front().y,
                                                 segment_points.back().x - segment_points.front().x);
                        double new_angle = atan2(points[j].y - segment_points.front().y,
                                                 points[j].x - segment_points.front().x);
                        if (std::abs(avg_angle - new_angle) > max_angle_difference_ / 2) continue;
                    }
                    
                    std::vector<Point2D> temp_buffer = segment_points;
                    temp_buffer.push_back(points[j]);
                    if (isLineFitValid(temp_buffer)) {
                        segment_points.push_back(points[j]);
                        used[j] = true;
                    }
                }
            }

            if (segment_points.size() < 2) continue;
            if (!isLineFitValid(segment_points)) {
                if (segment_points.size() > 3) {
                    size_t mid = segment_points.size() / 2;
                    line_segments.emplace_back(segment_points.front(), segment_points[mid]);
                    line_segments.emplace_back(segment_points[mid], segment_points.back());
                    continue;
                }
                continue;
            }

            line_segments.emplace_back(segment_points.front(), segment_points.back());
        }
        return line_segments;
    }

    bool isLineFitValid(const std::vector<Point2D>& segment_points) {
        if (segment_points.size() < 2) return false;

        double sum_x = 0, sum_y = 0, sum_x2 = 0, sum_xy = 0;
        size_t n = segment_points.size();
        for (const auto& p : segment_points) {
            sum_x += p.x;
            sum_y += p.y;
            sum_x2 += p.x * p.x;
            sum_xy += p.x * p.y;
        }
        double denominator = n * sum_x2 - sum_x * sum_x;
        if (std::abs(denominator) < 1e-6) {
            return validateVerticalFit(segment_points);
        }
        double slope = (n * sum_xy - sum_x * sum_y) / denominator;
        double intercept = (sum_y - slope * sum_x) / n;

        double total_error = 0.0;
        for (const auto& p : segment_points) {
            double estimated_y = slope * p.x + intercept;
            total_error += std::pow(p.y - estimated_y, 2);
        }
        return (total_error / n) < max_fitting_error_;
    }

    bool validateVerticalFit(const std::vector<Point2D>& segment_points) {
        double sum_x = 0;
        for (const auto& p : segment_points) {
            sum_x += p.x;
        }
        double mean_x = sum_x / segment_points.size();
    
        double total_error = 0.0;
        for (const auto& p : segment_points) {
            total_error += std::pow(p.x - mean_x, 2);
        }
        return (total_error / segment_points.size()) < max_fitting_error_;
    }
    

    void publishLines(const std::vector<std::pair<Point2D, Point2D>>& segments, const std_msgs::msg::Header& header) {
        messages::msg::LineSegmentList line_list;
        line_list.header = header;

        for (const auto& seg : segments) {
            double dx = seg.second.x - seg.first.x;
            double dy = seg.second.y - seg.first.y;
            double length = std::hypot(dx, dy);
            if (length < min_segment_length_) continue;

            messages::msg::LineSegment line;
            line.start.x = seg.first.x;
            line.start.y = seg.first.y;
            line.end.x = seg.second.x;
            line.end.y = seg.second.y;
            line.rho = std::hypot(seg.first.x, seg.first.y);
            line.alpha = std::atan2(seg.first.y, seg.first.x);
            line_list.segments.push_back(line);
        }
        pub_->publish(line_list);
    }
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<IncrementalLineFittingNode>());
    rclcpp::shutdown();
    return 0;
}
