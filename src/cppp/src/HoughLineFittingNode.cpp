#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <geometry_msgs/msg/point.hpp>
#include "messages/msg/line_segment.hpp"
#include "messages/msg/line_segment_list.hpp"
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <opencv2/opencv.hpp>

using std::placeholders::_1;

class HoughLineFittingNode : public rclcpp::Node {
public:
    HoughLineFittingNode() : Node("HoughLineFittingNode") {
        sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
            "/acc_filter", 10, std::bind(&HoughLineFittingNode::scanCallback, this, _1));
        pub_ = this->create_publisher<messages::msg::LineSegmentList>("/extracted_lines", 10);
        odom_sub_ = this->create_subscription<nav_msgs::msg::Odometry>(
            "/odom_fused", 10, std::bind(&HoughLineFittingNode::odomCallback, this, _1));
    }

private:
    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr sub_;
    rclcpp::Publisher<messages::msg::LineSegmentList>::SharedPtr pub_;
    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub_;
    std::array<double, 4> current_pose_cov_ = {0.0, 0.0, 0.0, 0.0}; // 2x2 flattened: [xx, xy, yx, yy]

    double angular_velocity_threshold_ = 0.2;
    double current_angular_velocity_ = 0.0;
    double min_segment_length_ = 0.7;  
    double rho_resolution_ = 1.0;     
    double theta_resolution_ = CV_PI / 360; 
    int hough_threshold_ = 20;       
    double max_gap_ = 10;             

    struct Point2D {
        double x, y;
    };

    void odomCallback(const nav_msgs::msg::Odometry::SharedPtr msg) {
        current_angular_velocity_ = std::abs(msg->twist.twist.angular.z);
        current_pose_cov_[0] = msg->pose.covariance[0];  // xx
        current_pose_cov_[1] = msg->pose.covariance[1];  // xy
        current_pose_cov_[2] = msg->pose.covariance[6];  // yx
        current_pose_cov_[3] = msg->pose.covariance[7];
    }

    void scanCallback(const sensor_msgs::msg::PointCloud2::SharedPtr msg) {
        if (current_angular_velocity_ > angular_velocity_threshold_) {
            return;
        }

        pcl::PointCloud<pcl::PointXYZ> pcl_cloud;
        pcl::fromROSMsg(*msg, pcl_cloud);
        std::vector<Point2D> points;
        for (const auto& p : pcl_cloud.points) {
            points.push_back({p.x, p.y});
        }

        auto line_segments = applyHoughTransform(points);
        publishLines(line_segments, msg->header);
    }

    std::vector<std::pair<Point2D, Point2D>> applyHoughTransform(const std::vector<Point2D>& points) {
        std::vector<std::pair<Point2D, Point2D>> line_segments;
        if (points.size() < 2) return line_segments;


        double min_x = std::numeric_limits<double>::max();
        double min_y = std::numeric_limits<double>::max();
        double max_x = std::numeric_limits<double>::lowest();
        double max_y = std::numeric_limits<double>::lowest();
        for (const auto& p : points) {
            min_x = std::min(min_x, p.x);
            min_y = std::min(min_y, p.y);
            max_x = std::max(max_x, p.x);
            max_y = std::max(max_y, p.y);
        }

        int img_width = static_cast<int>((max_x - min_x) * 100);
        int img_height = static_cast<int>((max_y - min_y) * 100);
        if (img_width < 10 || img_height < 10) return line_segments;

        cv::Mat img = cv::Mat::zeros(img_height, img_width, CV_8UC1);

        for (const auto& p : points) {
            int px = static_cast<int>((p.x - min_x) * 100);
            int py = static_cast<int>((p.y - min_y) * 100);
            if (px >= 0 && px < img_width && py >= 0 && py < img_height) {
                img.at<uint8_t>(py, px) = 255;
            }
        }

        std::vector<cv::Vec4i> lines;
        cv::HoughLinesP(img, lines, rho_resolution_, theta_resolution_, hough_threshold_, min_segment_length_ * 100, max_gap_);

        for (const auto& l : lines) {
            Point2D start{l[0] / 100.0 + min_x, l[1] / 100.0 + min_y};
            Point2D end{l[2] / 100.0 + min_x, l[3] / 100.0 + min_y};
            if (std::hypot(end.x - start.x, end.y - start.y) >= min_segment_length_) {
                line_segments.emplace_back(start, end);
            }
        }

        return line_segments;
    }
    std::array<double, 4> computeSegmentCovariance(const Point2D& p1, const Point2D& p2) {
        // Assume Gaussian noise in points and add pose covariance
        const double lidar_noise_var = 0.01 * 0.01;
    
        std::array<double, 4> cov;
        cov[0] = lidar_noise_var + current_pose_cov_[0];  // var(x)
        cov[1] = current_pose_cov_[1];                    // cov(x,y)
        cov[2] = current_pose_cov_[2];                    // cov(y,x)
        cov[3] = lidar_noise_var + current_pose_cov_[3];  // var(y)
    
        return cov;
    }    

    void publishLines(const std::vector<std::pair<Point2D, Point2D>>& segments, const std_msgs::msg::Header& header) {

        messages::msg::LineSegmentList line_list;
        line_list.header = header;

        for (const auto& seg : segments) {
            messages::msg::LineSegment line;
            line.start.x = seg.first.x;
            line.start.y = seg.first.y;
            line.end.x = seg.second.x;
            line.end.y = seg.second.y;
            line.rho = std::hypot(seg.first.x, seg.first.y);
            line.alpha = std::atan2(seg.first.y, seg.first.x);
            auto cov = computeSegmentCovariance(seg.first, seg.second);
            line.covariance[0] = cov[0];
            line.covariance[1] = cov[1];
            line.covariance[2] = cov[2];
            line.covariance[3] = cov[3];

            line_list.segments.push_back(line);
        }


        pub_->publish(line_list);
    }
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<HoughLineFittingNode>());
    rclcpp::shutdown();
    return 0;
}