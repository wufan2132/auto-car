#include "ros/ros.h"
#include "chassis/car_chassis.h"
#include "car_msgs/chassis.h"

int main(int argc, char **argv){
  ros::init(argc, argv, "chassis");

  // CarChassis car_chassis;
  // car_chassis.Init();
  
  // ros::NodeHandle car_chassis_NodeHandle;
  // ros::Subscriber chassisCommand_subscriber = car_chassis_NodeHandle.subscribe("prius", 1, &CarChassis::chassisCommand_topic_callback, &car_chassis);

  ros::spin();
  return 0;
}