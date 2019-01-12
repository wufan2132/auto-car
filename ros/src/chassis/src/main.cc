#include "ros/ros.h"
#include "chassis/car_chassis.h"
#include "car_msgs/chassis.h"
#include "nav_msgs/Odometry.h" 
#include "tf/transform_datatypes.h"
#include "car_msgs/localization.h"
#include "car_msgs/chassis.h"
#include <Eigen/Dense>
#include "geometry_msgs/Quaternion.h" 
#include "geometry_msgs/Transform.h"
#include "tf2_msgs/TFMessage.h"
#include "sensor_msgs/Imu.h"
#include "math/euler_angles_zxy.h"

ros::Publisher localization_msg_Publisher;
ros::Publisher chassis_msg_Publisher;
ros::Publisher imu_msg_Publisher;
car_msgs::localization car_localization;
car_msgs::chassis car_chassis;

#if SIMULATE //use gazebo simulate
//单位m
#define POSITION_OFFSET 1

void chassis_topic_callback(const nav_msgs::Odometry::ConstPtr &chassis_msg){

  double roll, pitch, yaw;
  tf::Quaternion quat;
  //获取定位、航向信息
  car_localization.header = chassis_msg->header;

  tf::quaternionMsgToTF(chassis_msg->pose.pose.orientation, quat);
  tf::Matrix3x3 RX = tf::Matrix3x3(quat);
  RX.getRPY(roll, pitch, yaw);
  car_localization.angle.x = roll;
  car_localization.angle.y = pitch;
  car_localization.angle.z = yaw;
  car_localization.angular_velocity = chassis_msg->twist.twist.angular;

  car_localization.position = chassis_msg->pose.pose.position;
  car_localization.position.x += POSITION_OFFSET*cos(yaw);
  car_localization.position.y += POSITION_OFFSET*sin(yaw);

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
void imu_topic_callback(const sensor_msgs::Imu::ConstPtr & imu_msg){

  car_chassis.acc.x = -imu_msg->linear_acceleration.x;
  car_chassis.acc.y = imu_msg->linear_acceleration.y;
  car_chassis.acc.z = imu_msg->linear_acceleration.z;
  
}
#else //use nvidia run
#include "usart.h"
using namespace std;
using namespace boost::asio;
Usart car_chassis_usart("/dev/ttyTHS2");
//to m/s2
#define ACC_RATE 55
#define DEC_RATE 130
void control_cmd_subscrib_callback(const car_msgs::control_cmd &control_cmd_msg){
 
 car_chassis_usart.send_to_serial((uint16_t)(control_cmd_msg.throttle * ACC_RATE),
                                   (uint16_t)(control_cmd_msg.brake * DEC_RATE),
                                     (int16_t)control_cmd_msg.steer);
}

geometry_msgs::Transform car_transform;
void tf_subscrib_callback(const tf2_msgs::TFMessage::ConstPtr &TF_msg){
  car_transform = TF_msg->transforms[1].transform;
}

void chassis_publish_callback(const ros::TimerEvent&){
  char flag;
  car_chassis_usart.reveive_from_serial(car_chassis.speed.x,
                                        car_localization.angle.x,
                                        car_localization.angle.y,
                                        car_localization.angle.z,
                                        car_chassis.acc.x,
                                        car_chassis.acc.y,
                                        car_chassis.acc.z,
                                        car_localization.angular_velocity.x,
                                        car_localization.angular_velocity.y,
                                        car_localization.angular_velocity.z,
                                        flag);
  car_localization.position.x = car_transform.translation.x;
  car_localization.position.y = car_transform.translation.y;
  car_localization.position.z = car_transform.translation.z;

  common::math::EulerAnglesZXY<double> EulerAngles(car_transform.rotation.w,
                                           	car_transform.rotation.x,
                                           	car_transform.rotation.y,
                                           	car_transform.rotation.z);

  // car_localization.angle.x = EulerAngles.pitch();
  // car_localization.angle.y = EulerAngles.yaw();
  car_localization.angle.z = EulerAngles.yaw();

  car_localization.angle.y = -car_localization.angle.y;
  car_localization.angular_velocity.y = -car_localization.angular_velocity.y;
  car_localization.header.stamp = ros::Time::now();
  
  car_chassis.header.stamp = car_localization.header.stamp; 

  sensor_msgs::Imu imu_msg;
  Eigen::Matrix3d R;
  Eigen::Quaterniond q;
  imu_msg.header.stamp = ros::Time::now();
  imu_msg.header.frame_id = "imu_link";

  R = Eigen::AngleAxisd(car_localization.angle.z, Eigen::Vector3d::UnitZ())
  * Eigen::AngleAxisd(car_localization.angle.y, Eigen::Vector3d::UnitY())
  * Eigen::AngleAxisd(car_localization.angle.x, Eigen::Vector3d::UnitX());
  //RotationMatrix to Quaterniond
  q = R;

  imu_msg.orientation.x = 0;//q.x();
  imu_msg.orientation.y = 0;//q.y();
  imu_msg.orientation.z = 0;//q.z();
  imu_msg.orientation.w = 0;//q.w();

  #define RATE 0.001064225 //(pi/180)*0.0609756

  imu_msg.angular_velocity.x = RATE * car_localization.angular_velocity.x;
  imu_msg.angular_velocity.y = RATE * car_localization.angular_velocity.y;
  imu_msg.angular_velocity.z = RATE * car_localization.angular_velocity.z;

  imu_msg.linear_acceleration.x = car_chassis.acc.x;
  imu_msg.linear_acceleration.y = car_chassis.acc.y;
  imu_msg.linear_acceleration.z = car_chassis.acc.z;

  localization_msg_Publisher.publish(car_localization);
  chassis_msg_Publisher.publish(car_chassis);
  imu_msg_Publisher.publish(imu_msg);
}
#endif


int main(int argc, char **argv){
  
  ros::init(argc, argv, "chassis");
  
  ros::NodeHandle car_chassis_NodeHandle;
  #if SIMULATE  //use gazebo simulate
  ros::Subscriber chassis_msg_subscriber = car_chassis_NodeHandle.subscribe("base_pose_ground_truth", 1, chassis_topic_callback);
  ros::Subscriber imu_msg_subscriber = car_chassis_NodeHandle.subscribe("imu", 1, imu_topic_callback);
  #else //use nvidia run
  ros::Subscriber control_cmd_msg_subscriber = car_chassis_NodeHandle.subscribe("prius", 1, control_cmd_subscrib_callback);
  ros::Timer cycle_timer = car_chassis_NodeHandle.createTimer(ros::Duration(0.005),chassis_publish_callback);
  imu_msg_Publisher = car_chassis_NodeHandle.advertise<sensor_msgs::Imu>("imu", 100);
  ros::Subscriber tf_msg_subscriber = car_chassis_NodeHandle.subscribe("tf", 1, tf_subscrib_callback);
  #endif

  localization_msg_Publisher = car_chassis_NodeHandle.advertise<car_msgs::localization>("localization_topic", 1000);
  chassis_msg_Publisher = car_chassis_NodeHandle.advertise<car_msgs::chassis>("chassis_topic", 1000);
  ros::spin();
  return 0;
}
