
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int16.h"
#include "std_msgs/Float64MultiArray.h"
#include <iterator>





void stringCallback(const std_msgs::String::ConstPtr& msg)
{
    ROS_INFO("(heard) String\t\t\t %s\n", msg->data.c_str());
}

void int16Callback(const std_msgs::Int16::ConstPtr& msg)
{
    ROS_INFO("(heard) Int16\t\t\t %d\n", msg->data);
}


void floatArrCallback(const std_msgs::Float64MultiArray::ConstPtr& msg)
{
   std::stringstream ss;
    for (size_t i = 0; i < msg->data.size(); ++i)
    {
        if (i != msg->data.size() - 1)
            ss << msg->data[i] << ",";
        else
            ss << msg->data[i];
    }

    std_msgs::String result_msg;
    result_msg.data = ss.str();

    ROS_INFO("(heard) Float64[]\t %s", result_msg.data.c_str());
  
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "listener");
    ros::NodeHandle node;

    ros::Subscriber subString = node.subscribe("chatter", 1000, stringCallback);
    ros::Subscriber subInt16 = node.subscribe("chatter_int16", 1000, int16Callback);
    ros::Subscriber subFloatArr = node.subscribe("chatter_float64", 1000, floatArrCallback);

    ros::spin();

    return 0;
}
