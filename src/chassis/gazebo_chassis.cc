#include "gazebo_chassis.h"

namespace chassis {

GazeboChassis(YAML::Node yaml_conf) { AINFO << "gazebo chassis start..."; }

void Init(ros::NodeHandle *node_handle) {
  // subscriber
  imu_subscriber_ =
      node_handle->subscribe("imu", 1, &GazeboChassis::imu_callback, this);
  pose_subscriber_ = node_handle->subscribe(
      "base_pose_ground_truth", 1, &GazeboChassis::pose_callback, this);
  // publisher
  ros::Publisher localization_publisher_;
  ros::Publisher pose_publisher_;
  // send mode
  if (conf_.mode == "preiod") {
    AINFO << "Send mode: preiod";
    timer_ = node_handle.createTimer(ros::Duration(conf_.send_preiod),
                                     &GazeboChassis::RunOnce, this);
  } else if (conf_.mode == "callback") {
    AINFO << "Send mode: callback";

  } else {
    AERROR << "Send mode: unknown!";
    ros::shutdown();
  }
}
void RunOnce(){};

void Stop() { AINFO << "gazebo chassis stop..."; };

};  // namespace chassis

}  // namespace chassis