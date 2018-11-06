#include "ros/ros.h"
#include "control/controller.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "controller");
  Controller controller;
  controller.Init();

  ros::NodeHandle controller_NodeHandle;
  // 创建ros定时器
  ros::Timer cycle_timer = controller_NodeHandle.createTimer(ros::Duration(0.01),&Controller::OnTimer, &controller);
  ros::Subscriber localization_publisher = controller_NodeHandle.subscribe("localization_topic", 1, &Controller::localization_topic_callback, &controller);
  ros::Subscriber chassis_publisher = controller_NodeHandle.subscribe("chassis_topic", 1, &Controller::chassis_topic_callback, &controller);
  ros::Subscriber path_publisher = controller_NodeHandle.subscribe("path_topic", 1, &Controller::path_topic_callback, &controller);

  ros::spin();
  return 0;
}
