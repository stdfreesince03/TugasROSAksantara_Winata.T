

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Pose2D.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <turtlesim/Spawn.h>       
#include <turtlesim/Kill.h>        
#include <math.h> 


ros::Publisher velocity_pub;
turtlesim::Pose current_pose;
ros:: ServiceClient spawn_client;
ros:: ServiceClient kill_client;
turtlesim::Kill ::Request kill_req;
turtlesim ::Kill::Response kill_resp;
turtlesim :: Spawn::Request spawn_req;
turtlesim :: Spawn:: Response spawn_resp;

void setup(){
  
    kill_req.name = "turtle1";
    ros::service::waitForService("/kill",ros::Duration(5));
    kill_client.call(kill_req,kill_resp);

   
    spawn_req.x = 1;
    spawn_req.y = 10;
    spawn_req.theta = 225;
    spawn_req.name ="turtle1";
    ros::service::waitForService("/spawn",ros::Duration(5));
    spawn_client.call(spawn_req,spawn_resp);

}


void poseCallback(const turtlesim::Pose::ConstPtr& pose)
{
  current_pose = *pose;
}


void moveStraight(double distance, double linear_speed)
{
  double initial_x = current_pose.x;
  double initial_y = current_pose.y;
  double traveled_distance = 0.0;

  geometry_msgs::Twist velocity;
  velocity.linear.x = linear_speed;

  while (traveled_distance < distance && ros::ok())
  {
    velocity_pub.publish(velocity);
    ros::spinOnce();

    double dx = current_pose.x - initial_x;
    double dy = current_pose.y - initial_y;
    traveled_distance = std::sqrt(dx * dx + dy * dy);
  }

  velocity.linear.x = 0;
  velocity_pub.publish(velocity);
}


void rotate(double angle, double angular_speed)
{
  double initial_yaw = current_pose.theta;
  double rotated_angle = 0.0;

  geometry_msgs::Twist velocity;
  velocity.angular.z = angular_speed;

  while (rotated_angle < angle && ros::ok())
  {
    velocity_pub.publish(velocity);
    ros::spinOnce();

    rotated_angle = std::abs(current_pose.theta - initial_yaw);
  }

  velocity.angular.z = 0;
  velocity_pub.publish(velocity);
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "w_shape_node");

  ros::NodeHandle nh;

  
  ros::Subscriber pose_sub = nh.subscribe<turtlesim::Pose>("turtle1/pose", 10, poseCallback);


  velocity_pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10);
  spawn_client = nh.serviceClient<turtlesim::Spawn>("/spawn");
  kill_client = nh.serviceClient<turtlesim::Kill>("/kill");

  setup();

  
  while (current_pose.x == 0.0 && current_pose.y == 0.0 && current_pose.theta == 0.0 && ros::ok())
  {
    ros::spinOnce();
    
  }


  moveStraight(5.0, 2.0);    
  rotate(2.356, 1.0);        
  moveStraight(3.0, 2.0);    
  rotate(3.92, 1.0);   
  rotate(2.05, 1.0);       
  moveStraight(3.0, 2.0);     
  rotate(2.4, 1.0);        
  moveStraight(5.0, 2.0);   

  ros::spin();
  return 0;
}