#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <sensor_msgs/point_cloud2_iterator.hpp>

class PreprocessNode : public rclcpp::Node {
public:
    PreprocessNode() : Node("PreprocessNode") {
        this->declare_parameter("max_range", 5.0);
        max_range_ = this->get_parameter("max_range").as_double();
        RCLCPP_INFO(this->get_logger(), "Max range parameter: %f", max_range_);

        sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
            "/accumulated_scan", 10,
            std::bind(&PreprocessNode::filterPoints, this, std::placeholders::_1));

        pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/acc_filter_lid_frame", 10);
    }

private:
    void filterPoints(const sensor_msgs::msg::PointCloud2::SharedPtr msg) {
     
        auto output = *msg;

      
        sensor_msgs::PointCloud2Iterator<float> iter_x(*msg, "x");
        sensor_msgs::PointCloud2Iterator<float> iter_y(*msg, "y");
        sensor_msgs::PointCloud2Iterator<float> iter_z(*msg, "z");

     
        sensor_msgs::PointCloud2Modifier modifier(output);
        modifier.setPointCloud2FieldsByString(1, "xyz");
        modifier.resize(0);

       
        for (; iter_x != iter_x.end(); ++iter_x, ++iter_y, ++iter_z) {
            float distance = std::sqrt((*iter_x) * (*iter_x) + (*iter_y) * (*iter_y));
            if (distance <= max_range_) {
             
                modifier.resize(modifier.size() + 1);
                
         
                sensor_msgs::PointCloud2Iterator<float> out_x(output, "x");
                sensor_msgs::PointCloud2Iterator<float> out_y(output, "y");
                sensor_msgs::PointCloud2Iterator<float> out_z(output, "z");

                *(out_x + (modifier.size() - 1)) = *iter_x;
                *(out_y + (modifier.size() - 1)) = *iter_y;
                *(out_z + (modifier.size() - 1)) = *iter_z;
            }
        }


        pub_->publish(output);
    }

    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr sub_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pub_;
    double max_range_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PreprocessNode>());
    rclcpp::shutdown();
    return 0;
}
