

#pragma once

#include <Eigen/Dense>
#include <memory>
#include "car_msgs/chassis.h"
#include "car_msgs/localization.h"
#include "chassis.h"
#include "chassis/car_chassis.h"
#include "chassis/common/chassis_gflags.h"
#include "common/base/file_tool/file_tool.h"
#include "common/base/global_gflags/global_gflags.h"
#include "common/util/activator.h"
#include "geometry_msgs/Quaternion.h"
#include "geometry_msgs/Transform.h"
#include "nav_msgs/Odometry.h"
#include "sensor_msgs/Imu.h"
#include "tf/transform_datatypes.h"
#include "tf2_msgs/TFMessage.h"

namespace chassis {

class GazeboChassis : public Chassis {
 public:
  GazeboChassis(const YAML::Node& yaml_conf);
  ~GazeboChassis() override;

  void Init(ros::NodeHandle *node_handle) override;
  void RunOnce() override;
  void Stop() override;

  std::string name() const { return "gazebo chassis"; };
  // callback
  void OdoCallback(const nav_msgs::Odometry::ConstPtr &odo_msg);
  void ImuCallback(const sensor_msgs::Imu::ConstPtr &imu_msg);
  // TimerCallBack
  void OnTimer(const ros::TimerEvent &);

 private:
  // Timer
  ros::Timer timer_;
  // subscriber
  ros::Subscriber odo_subscriber_;
  ros::Subscriber imu_subscriber_;
  // publisher
  ros::Publisher localization_publisher_;
  ros::Publisher car_state_publisher_;
  // message buf
  car_msgs::localization car_localization_;
  car_msgs::chassis car_state_;
  //
  struct Conf {
    std::string send_mode;
    double send_period;
  };
  Conf conf_;
  //
  std::unique_ptr<common::util::Activator> activator_;
};

}  // namespace chassis