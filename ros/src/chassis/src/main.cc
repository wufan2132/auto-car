#include "ros/ros.h"
#include "chassis/car_chassis.h"
#include "car_msgs/chassis.h"
#include "nav_msgs/Odometry.h" 
#include "tf/transform_datatypes.h"
#include "car_msgs/localization.h"
#include "car_msgs/chassis.h"

ros::Publisher localization_msg_Publisher;
ros::Publisher chassis_msg_Publisher;

void chassis_topic_callback(const nav_msgs::Odometry::ConstPtr &chassis_msg){
  car_msgs::localization car_localization;
  car_msgs::chassis car_chassis;

  car_localization.position = chassis_msg->pose.pose.position;
  tf::Quaternion quat;
  tf::quaternionMsgToTF(chassis_msg->pose.pose.orientation, quat);
  double roll, pitch, yaw;
  tf::Matrix3x3(quat).getRPY(roll, pitch, yaw);
  car_localization.angle.x = roll;
  car_localization.angle.y = pitch;
  car_localization.angle.z = yaw;

  chassis_msg->twist.twist.linear;

  localization_msg_Publisher.publish(car_localization);
}

int main(int argc, char **argv){
  ros::init(argc, argv, "chassis");
  
  ros::NodeHandle car_chassis_NodeHandle;
  ros::Subscriber chassis_msg_subscriber = car_chassis_NodeHandle.subscribe("base_pose_ground_truth", 1, chassis_topic_callback);
  localization_msg_Publisher = car_chassis_NodeHandle.advertise<car_msgs::localization>("localization_topic", 1000);
  chassis_msg_Publisher = car_chassis_NodeHandle.advertise<car_msgs::chassis>("chassis_topic", 1000);
  ros::spin();
  return 0;
}