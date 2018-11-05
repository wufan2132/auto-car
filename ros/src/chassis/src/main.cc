#include "ros/ros.h"
#include "chassis/car_chassis.h"
#include "car_msgs/chassis.h"
#include "nav_msgs/Odometry.h" 
#include "tf/transform_datatypes.h"
#include "car_msgs/localization.h"
#include "car_msgs/chassis.h"
#include <Eigen/Dense>
#include "geometry_msgs/Quaternion.h" 

ros::Publisher localization_msg_Publisher;
ros::Publisher chassis_msg_Publisher;

void chassis_topic_callback(const nav_msgs::Odometry::ConstPtr &chassis_msg){

  car_msgs::localization car_localization;
  car_msgs::chassis car_chassis;

  double roll, pitch, yaw;
  tf::Quaternion quat;
  //获取定位、航向信息
  car_localization.header = chassis_msg->header;
  car_localization.position = chassis_msg->pose.pose.position;
  tf::quaternionMsgToTF(chassis_msg->pose.pose.orientation, quat);
  tf::Matrix3x3 RX = tf::Matrix3x3(quat);
  RX.getRPY(roll, pitch, yaw);
  car_localization.angle.x = roll;
  car_localization.angle.y = pitch;
  car_localization.angle.z = yaw;

  double speed_roll, speed_pitch, speed_yaw;
  double speed_roll_out, speed_pitch_out, speed_yaw_out;
  tf::Quaternion speed_quat;
  //获取速度信息
  car_chassis.header = chassis_msg->header;
  //定义车的世界坐标系下的坐标
  //定义归一化的四元数 把四元数Q1的虚部取负值，表示和原四元数相反的旋转，相当于将theta变为-theta
  Eigen::Quaterniond Q1;
  //定义车在世界坐标系下的线速度
  Eigen::Matrix <double,3,1> Lw(chassis_msg->twist.twist.linear.x,
                                chassis_msg->twist.twist.linear.y,
                                chassis_msg->twist.twist.linear.z);
  //定义车在车坐标下的线速度
  Eigen::Matrix <double,3,1> Lc;
  //给出世界坐标系下车的姿态
  Q1 = Eigen::Quaterniond(chassis_msg->pose.pose.orientation.w,
                          -chassis_msg->pose.pose.orientation.x,
                          -chassis_msg->pose.pose.orientation.y,
                          -chassis_msg->pose.pose.orientation.z).normalized();
  Lc = Q1*Lw;

  car_chassis.speed.x = Lc.x();
  car_chassis.speed.y = Lc.y();
  car_chassis.speed.z = Lc.z();

  localization_msg_Publisher.publish(car_localization);
  chassis_msg_Publisher.publish(car_chassis);
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