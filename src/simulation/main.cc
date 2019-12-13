#include <memory>
#include "simulation_factory.h"
#include "common/base/file_tool/file_tool.h"
#include "common/simulation_gflags.h"
#include "ros/ros.h"

using common::base::FileTool;

int main(int argc, char **argv) {
  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, true);

  ros::init(argc, argv, "simulation");
  ros::NodeHandle simulation_node_handle;

  simulation::SimulationFactory simulation_factory;
  std::unique_ptr<simulation::Simulation> simulation = simulation_factory.CreatObject(
      FLAGS_simulation_mode, FileTool::LoadFile(FLAGS_simulation_conf_path));
  simulation->Init(&simulation_node_handle);

  ros::spin();
  return 0;
}
