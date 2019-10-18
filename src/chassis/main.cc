#include <memory>
#include "chassis_factory.h"
#include "common/base/file_tool/file_tool.h"
#include "common/chassis_gflags.h"
#include "ros/ros.h"

using autocar::common::FileTool;

int main(int argc, char **argv) {
  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, true);

  ros::init(argc, argv, "chassis");
  ros::NodeHandle chassis_node_handle;

  chassis::ChassisFactory chassis_factory;
  std::unique_ptr<chassis::Chassis> chassis = chassis_factory.CreatObject(
      FLAGS_chassis_mode, FileTool::LoadFile(FLAGS_chassis_conf_path));
  chassis->Init(&chassis_node_handle);

  ros::spin();
  return 0;
}
