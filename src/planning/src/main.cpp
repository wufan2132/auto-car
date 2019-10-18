

#include "common/base/file_tool/file_tool.h"
#include "common/base/global_gflags/global_gflags.h"
#include "common/base/log.h"
#include "planning/common.h"
#include "planning/planning.h"
#include "planning/src/common/planning_gflags.h"

bool DEBUG = 0;
using autocar::common::FileTool;
int main(int argc, char **argv) {
  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, true);
  ROS_INFO("PLANNING start!!!!!");
  // //判断是否为debug模式
  // Common::debug_check();

  /* code for main function */
  ros::init(argc, argv, "planning");
  ros::NodeHandle planning_NodeHandle;

  /*planning模块初始化*/
  Car_Planning planning(FileTool::LoadFile(FLAGS_planning_conf_path));
  LOG(ERROR) << "FileTool::LoadFile";
  debugger = new Debugger();

  /*订阅*/
  planning.localization_subscriber = planning_NodeHandle.subscribe(
      "localization_topic", 1, &Car_Planning::localization_callback, &planning);
  planning.chassis_subscriber = planning_NodeHandle.subscribe(
      "chassis_topic", 1, &Car_Planning::chassis_callback, &planning);
  planning.obstacle_subscriber = planning_NodeHandle.subscribe(
      "obstacle_topic", 1, &Car_Planning::obstacle_callback, &planning);
  /*发布*/
  planning.refrenceline_publisher =
      planning_NodeHandle.advertise<car_msgs::trajectory>("refrenceline_topic",
                                                          1000);
  planning.trajectory_publisher =
      planning_NodeHandle.advertise<car_msgs::trajectory>("trajectory_topic",
                                                          1000);

  // debugger
  debugger->set_NodeHandle(&planning_NodeHandle);

  // planning_init
  planning.Init();
  // 创建ros定时器
  ros::Timer cycle_timer;
  if (planning.conf.mode == "send") {
    ROS_INFO("planning send mode!");
    cycle_timer = planning_NodeHandle.createTimer(
        ros::Duration(planning.conf.period), &Car_Planning::OnTimer, &planning);
  } else if (planning.conf.mode == "write") {
    ROS_INFO("planning write mode!");
  } else {
    ROS_ERROR("unknow planning mode!");
    ros::shutdown();
  }

  ros::spin();

  return 0;
}
