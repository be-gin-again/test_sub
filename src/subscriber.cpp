#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int64.hpp"

#include "test_msgs/msg/num.hpp"

using std::placeholders::_1;


class MinimalSubscriber : public rclcpp::Node
{
    public:
        MinimalSubscriber()
        : Node("subscriber")
        {
            subscription_ = this->create_subscription<test_msgs::msg::Num>(
                "topic",10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
        }

    private:
        void topic_callback(const test_msgs::msg::Num & msg) const
        {
            RCLCPP_INFO(this->get_logger(), "I heard '%ld'", msg.num);
        }

        rclcpp::Subscription<test_msgs::msg::Num>::SharedPtr subscription_;
};



int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MinimalSubscriber>());
    rclcpp::shutdown();
    return 0;
}