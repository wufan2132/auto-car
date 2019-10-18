

#pragma once

#include "chassis.h"
#include "common/base/file_tool/file_tool.h"

namespace chassis {

class GazeboChassis : public Chassis {
 public:
  GazeboChassis(YAML::Node yaml_conf);
  ~GazeboChassis() = default;

  void Init(ros::NodeHandle *node_handle);
  void RunOnce();
  void Stop();

  std::string name() const { return "gazebo chassis"; };
  // callback
  void pose_callback(const nav_msgs::Odometry::ConstPtr &pose_msg);
  void imu_callback(const sensor_msgs::Imu::ConstPtr &imu_msg);

 private:
  // Timer
  ros::Timer timer_;
  // subscriber
  ros::Subscriber pose_subscriber_;
  ros::Subscriber imu_subscriber_;
  // publisher
  ros::Publisher localization_publisher_;
  ros::Publisher pose_publisher_;
  // message buf
  car_msgs::localization car_localization_;
  car_msgs::chassis car_pose_;
  //
  struct Conf {
    string send_mode;
    double send_preiod;
  };
  Conf conf_;
};

}  // namespace chassis