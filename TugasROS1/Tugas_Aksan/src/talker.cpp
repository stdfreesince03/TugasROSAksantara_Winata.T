
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int16.h"
#include "std_msgs/Float64MultiArray.h"
#include <sstream>
#include <string>

using namespace ros;

   

int main(int argc, char **argv){
 
       ros::init(argc, argv, "talker");

	ros::NodeHandle n;
	
       ros::Publisher chatter_publisher = n.advertise<std_msgs::String>("chatter", 1000);
       ros::Publisher int_publisher = n.advertise<std_msgs::Int16 >("chatter_int16", 1000);
       ros::Publisher float_publisher = n.advertise<std_msgs::Float64MultiArray>("chatter_float64", 1000);
              
	ros::Rate loop_rate(0.5);

   
	std_msgs::String msg;
       std_msgs :: Int16 intMsg;
       std_msgs :: Float64MultiArray floatMsg;
      
	std::stringstream ss;
	ss << "Hello World ";
       msg.data = ss.str();


       intMsg.data = 22096;
    
		
	floatMsg.data.clear();
	for (int i = 0; i < 6; i++)
	{
	  floatMsg.data.push_back(rand() % 255);
	}
		
       ros::spinOnce(); 
       loop_rate.sleep();

       chatter_publisher.publish(msg);

       spinOnce();
       loop_rate.sleep();

       int_publisher.publish(intMsg);

       ros::spinOnce(); 
       loop_rate.sleep();
       float_publisher.publish(floatMsg);

       ros::spinOnce(); 
       loop_rate.sleep();
      
   
       return 0;
     
}