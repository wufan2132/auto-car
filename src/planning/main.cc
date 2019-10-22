

#include "common/base/file_tool/file_tool.h"
#include "common/base/global_gflags/global_gflags.h"
#include "common/base/log.h"
#include "planning.h"
#include "planning/common/planning_gflags.h"

using common::base::FileTool;

int main(int argc, char **argv) {
  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, true);
  AINFO << "planning start...";

  // ros_node
  ros::init(argc, argv, "planning");
  ros::NodeHandle node_handle;

  /*planning模块初始化*/
  planning::Planning planning(FileTool::LoadFile(FLAGS_planning_conf_path));
  planning.Init(&node_handle);
  // debugger = new Debugger();
  // debugger->set_NodeHandle(&node_handle);

  ros::spin();

  return 0;
}
