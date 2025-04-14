#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <geometry_msgs/msg/point.hpp>
#include "messages/msg/line_segment.hpp"
#include "messages/msg/line_segment_list.hpp"
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/sample_consensus/ransac.h>
#include <pcl/sample_consensus/sac_model_line.h>
#include <vector>
#include <cmath>
#include <limits>

using std::placeholders::_1;

class RANSACLineExtractionNode : public rclcpp::Node {
public:
    RANSACLineExtractionNode() : Node("RANSACLineExtractionNode") {
        sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
            "/acc_filter", 10, std::bind(&RANSACLineExtractionNode::scanCallback, this, _1));
        pub_ = this->create_publisher<messages::msg::LineSegmentList>("/extracted_lines", 10);
        odom_sub_ = this->create_subscription<nav_msgs::msg::Odometry>(
            "/odom_fused", 10, std::bind(&RANSACLineExtractionNode::odomCallback, this, _1));
        RCLCPP_INFO(this->get_logger(), "RANSAC Line Extraction Node initialized.");
    }

private:
    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr sub_;
    rclcpp::Publisher<messages::msg::LineSegmentList>::SharedPtr pub_;
    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub_;

    double angular_velocity_threshold_ = 0.2;
    double current_angular_velocity_ = 0.0;
    double distance_threshold_ = 0.95; // Clustering distance threshold
    double min_segment_length_ = 0.5;  // Minimum length for valid segments
    double boundary_threshold_ = 1.0;// Threshold to remove edge artifacts

    struct Point2D {
        double x, y;
    };

    void odomCallback(const nav_msgs::msg::Odometry::SharedPtr msg) {
        current_angular_velocity_ = std::abs(msg->twist.twist.angular.z);
    }

    void scanCallback(const sensor_msgs::msg::PointCloud2::SharedPtr msg) {
        if (current_angular_velocity_ > angular_velocity_threshold_) {
            return;
        }

        pcl::PointCloud<pcl::PointXYZ> pcl_cloud;
        pcl::fromROSMsg(*msg, pcl_cloud);
        std::vector<Point2D> points;

        auto min_x = std::numeric_limits<float>::max();
        auto max_x = std::numeric_limits<float>::lowest();
        auto min_y = std::numeric_limits<float>::max();
        auto max_y = std::numeric_limits<float>::lowest();


        for (const auto& p : pcl_cloud.points) {
            min_x = std::min(min_x, p.x);
            max_x = std::max(max_x, p.x);
            min_y = std::min(min_y, p.y);
            max_y = std::max(max_y, p.y);
        }

        for (const auto& p : pcl_cloud.points) {
            if (std::abs(p.x - min_x) < boundary_threshold_ || std::abs(p.x - max_x) < boundary_threshold_ ||
                std::abs(p.y - min_y) < boundary_threshold_ || std::abs(p.y - max_y) < boundary_threshold_) {
                continue; 
            }
            points.push_back({p.x, p.y});
        }

        auto clusters = clusterPoints(points);
        std::vector<std::pair<Point2D, Point2D>> line_segments;
        
        for (const auto& cluster : clusters) {
            auto segment = fitLineRANSAC(cluster);
            if (segment) {
                line_segments.push_back(segment.value());
            }
        }

        publishLines(line_segments, msg->header);
    }

    std::vector<std::vector<Point2D>> clusterPoints(const std::vector<Point2D>& points) {
        std::vector<std::vector<Point2D>> clusters;
        if (points.empty()) return clusters;
        
        std::vector<Point2D> current_cluster;
        current_cluster.push_back(points[0]);

        for (size_t i = 1; i < points.size(); ++i) {
            double dist = std::hypot(points[i].x - points[i - 1].x, points[i].y - points[i - 1].y);
            if (dist > distance_threshold_) {
                clusters.push_back(current_cluster);
                current_cluster.clear();
            }
            current_cluster.push_back(points[i]);
        }
        
        if (!current_cluster.empty()) {
            clusters.push_back(current_cluster);
        }
        
        return clusters;
    }

    std::optional<std::pair<Point2D, Point2D>> fitLineRANSAC(const std::vector<Point2D>& cluster) {
        if (cluster.size() < 3) return std::nullopt;

        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
        for (const auto& p : cluster) {
            cloud->push_back(pcl::PointXYZ(p.x, p.y, 0));
        }

        RCLCPP_INFO(this -> get_logger(), "Extracting Yayy");

        pcl::SampleConsensusModelLine<pcl::PointXYZ>::Ptr model(new pcl::SampleConsensusModelLine<pcl::PointXYZ>(cloud));
        pcl::RandomSampleConsensus<pcl::PointXYZ> ransac(model);
        ransac.setDistanceThreshold(0.35); 
        ransac.setMaxIterations(500);
        ransac.setProbability(0.99);

        if (!ransac.computeModel()) return std::nullopt;

        Eigen::VectorXf coeffs;
        ransac.getModelCoefficients(coeffs);

       
        double x0 = coeffs[0], y0 = coeffs[1];
        double dx = coeffs[3], dy = coeffs[4];

        double min_proj = std::numeric_limits<double>::max();
        double max_proj = std::numeric_limits<double>::lowest();

        for (const auto& p : cluster) {
            double proj = (p.x - x0) * dx + (p.y - y0) * dy;
            min_proj = std::min(min_proj, proj);
            max_proj = std::max(max_proj, proj);
        }

        Point2D start = {x0 + min_proj * dx, y0 + min_proj * dy};
        Point2D end = {x0 + max_proj * dx, y0 + max_proj * dy};

        if (std::abs(max_proj - min_proj) < min_segment_length_) {
            return std::nullopt;
        }
        

        return std::make_pair(start, end);
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
            line_list.segments.push_back(line);
        }
        
        pub_->publish(line_list);
    }
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<RANSACLineExtractionNode>());
    rclcpp::shutdown();
    return 0;
}
