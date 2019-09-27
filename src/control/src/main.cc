#include "ros/ros.h"
#include "control/control.h"
using namespace control;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "controller");
  Control control;
  control.Init();

  ros::NodeHandle control_NodeHandle;
  // 创建ros定时器
  ros::Timer cycle_timer = control_NodeHandle.createTimer(ros::Duration(0.01),&Control::OnTimer, &control);
  ros::Subscriber localization_subscriber = control_NodeHandle.subscribe("localization_topic", 1, &Control::localization_topic_callback, &control);
  ros::Subscriber chassis_subscriber = control_NodeHandle.subscribe("chassis_topic", 1, &Control::chassis_topic_callback, &control);
  ros::Subscriber path_subscriber = control_NodeHandle.subscribe("trajectory_topic", 1, &Control::path_topic_callback, &control);
  ros::Subscriber param_subscriber = control_NodeHandle.subscribe("param_topic", 1, &Control::param_topic_callback, &control);
  ros::spin();
  return 0;
}
