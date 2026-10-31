#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"

class PoseSubscriber : public rclcpp::Node {
public:
    PoseSubscriber() : Node("pose_subscriber")
    {
        sub_ = this->create_subscription<geometry_msgs::msg::PoseStamped>("/goal_pose", 10,
            [this](const geometry_msgs::msg::PoseStamped::SharedPtr msg) {
                RCLCPP_INFO(this->get_logger(), "接收 x=%.2f, y=%.2f", msg->pose.position.x, msg->pose.position.y);
            });
    }

private:
    rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr sub_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<PoseSubscriber>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}