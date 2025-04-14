#include <rclcpp/rclcpp.hpp>
#include <messages/msg/line_segment_list.hpp>
#include <messages/msg/line_segment.hpp>
#include <vector>
#include <cmath>
#include <Eigen/Dense>
#include <unordered_map>

class LandmarkGraphNode : public rclcpp::Node {
public:
    LandmarkGraphNode() : Node("landmark_graph") {
        line_sub_ = this->create_subscription<messages::msg::LineSegmentList>(
            "/transformed_lines", 10, std::bind(&LandmarkGraphNode::line_callback, this, std::placeholders::_1));
        graph_pub_ = this->create_publisher<messages::msg::LineSegmentList>("/landmark_graph", 10);
    }

private:
    struct Landmark {
        int id;
        float rho, alpha;
        Eigen::Matrix2f covariance;
        geometry_msgs::msg::Point start, end;
        int age;
    };

    std::unordered_map<int, Landmark> landmarks_;
    int next_landmark_id_ = 0;

    void line_callback(const messages::msg::LineSegmentList::SharedPtr msg) {
        std::unordered_map<int, bool> matched;
        for (const auto& segment : msg->segments) {
            bool found_match = false;
            int matched_id = -1;
            
            for (auto& [id, landmark] : landmarks_) {
                if (is_similar(segment, landmark)) {
                    matched_id = id;
                    found_match = true;
                    break;
                }
            }
            
            if (found_match) {
                update_landmark(landmarks_[matched_id], segment);
                matched[matched_id] = true;
            } else {
                add_new_landmark(segment);
            }
        }
        

        std::vector<int> to_remove;
        for (auto& [id, landmark] : landmarks_) {
            if (!matched[id]) {
                landmark.age--;
                if (landmark.age <= 0) {
                    to_remove.push_back(id);
                }
            }
        }
        for (int id : to_remove) {
            landmarks_.erase(id);
        }

        publish_landmarks(msg->header);
    }

    bool is_similar(const messages::msg::LineSegment& segment, const Landmark& landmark) {
        float rho_diff = std::abs(segment.rho - landmark.rho);
        float alpha_diff = std::abs(segment.alpha - landmark.alpha);
        return (rho_diff < 0.1 && alpha_diff < 0.05);
    }

    void update_landmark(Landmark& landmark, const messages::msg::LineSegment& segment) {
        landmark.rho = (landmark.rho + segment.rho) / 2.0;
        landmark.alpha = (landmark.alpha + segment.alpha) / 2.0;
        landmark.start = segment.start;
        landmark.end = segment.end;
        landmark.age = 5;
    }

    void add_new_landmark(const messages::msg::LineSegment& segment) {
        Landmark new_landmark;
        new_landmark.id = next_landmark_id_++;
        new_landmark.rho = segment.rho;
        new_landmark.alpha = segment.alpha;
        new_landmark.start = segment.start;
        new_landmark.end = segment.end;
        new_landmark.covariance = Eigen::Matrix2f::Identity() * 0.01;
        new_landmark.age = 5;
        landmarks_[new_landmark.id] = new_landmark;
    }

    void publish_landmarks(const std_msgs::msg::Header& header) {
        messages::msg::LineSegmentList msg;
        msg.header = header;
        for (const auto& [id, landmark] : landmarks_) {
            messages::msg::LineSegment line_msg;
            line_msg.rho = landmark.rho;
            line_msg.alpha = landmark.alpha;
            line_msg.start = landmark.start;
            line_msg.end = landmark.end;
            for (int i = 0; i < 4; ++i) line_msg.covariance[i] = landmark.covariance(i / 2, i % 2);
            msg.segments.push_back(line_msg);
        }
        
        graph_pub_->publish(msg);
    }

    rclcpp::Subscription<messages::msg::LineSegmentList>::SharedPtr line_sub_;
    rclcpp::Publisher<messages::msg::LineSegmentList>::SharedPtr graph_pub_;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<LandmarkGraphNode>());
    rclcpp::shutdown();
    return 0;
}
