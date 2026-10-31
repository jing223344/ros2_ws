#include <memory>
#include <chrono>
#include <functional>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"

class PosePublisher : public rclcpp::Node {
public:
    PosePublisher() : Node("pose_publisher")
    {
        pub_ = this->create_publisher<geometry_msgs::msg::PoseStamped>("/goal_pose", 10);
        timer_ = this->create_wall_timer(std::chrono::seconds(1),std::bind(&PosePublisher::timerCallback, this));
    }

private:
    void timerCallback() {
        auto msg = geometry_msgs::msg::PoseStamped();
        msg.pose.position.x = 1.0;
        msg.pose.position.y = 2.0;
        pub_->publish(msg);
        RCLCPP_INFO(this->get_logger(), "发送 x=%.2f, y=%.2f", msg.pose.position.x, msg.pose.position.y);
    }
    rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr pub_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<PosePublisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}