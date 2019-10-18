#include "gazebo_chassis.h"

namespace chassis {

GazeboChassis::GazeboChassis(YAML::Node yaml_conf) : Chassis(yaml_conf) {
  AINFO << "gazebo chassis start...";
}

GazeboChassis::~GazeboChassis() { this->Stop(); }

void GazeboChassis::Init(ros::NodeHandle *node_handle) {
  // subscriber
  imu_subscriber_ =
      node_handle->subscribe("imu", 1, &GazeboChassis::ImuCallback, this);
  pose_subscriber_ = node_handle->subscribe("base_pose_ground_truth", 1,
                                            &GazeboChassis::PoseCallback, this);
  // send mode
  if (this->mode() == "preiod") {
    AINFO << "Send mode: preiod";
    timer_ = node_handle->createTimer(ros::Duration(conf_.send_preiod),
                                      &GazeboChassis::OnTimer, this);
  } else if (this->mode() == "callback") {
    AINFO << "Send mode: callback";

  } else {
    AERROR << "Send mode: unknown!";
    ros::shutdown();
  }
}

void GazeboChassis::PoseCallback(const nav_msgs::Odometry::ConstPtr &pose_msg) {
}
void GazeboChassis::ImuCallback(const sensor_msgs::Imu::ConstPtr &imu_msg) {}

void GazeboChassis::OnTimer(const ros::TimerEvent &) { this->RunOnce(); }
void GazeboChassis::RunOnce(){};

void GazeboChassis::Stop() { AINFO << "gazebo chassis stop..."; };

};  // namespace chassis
