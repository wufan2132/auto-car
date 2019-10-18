#include <memory>
#include "ros/ros.h"

int main(int argc, char **argv) {
  ros::init(argc, argv, "chassis");
  ros::NodeHandle chassis_node_handle;

  chassis::ChassisFactory chassis_factory;
  std::unique_ptr<chassis::Chassis> chassis =
      chassis_factory.CreatObject(FLAGS_chassis_mode);
  chassis->Init();

  ros::spin();
  return 0;
}
