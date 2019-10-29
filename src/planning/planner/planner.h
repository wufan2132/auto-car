#pragma once

#include <Eigen/Dense>
#include <vector>
#include "car_msgs/trajectory.h"
#include "car_msgs/trajectory_point.h"
#include "planning/coordinate/car_state_sl.h"
#include "planning/tasks/task.h"
#include "planning/tool/Fitting.h"
#include "yaml-cpp/yaml.h"

namespace planning {

class Planner : public Task {
 public:
  Planner(const common::base::ConfNode& yaml_conf) : Task(yaml_conf){};
  virtual ~Planner() = default;

  virtual bool Init() = 0;
  virtual bool Run(Frame* frame) = 0;
  virtual bool Stop() = 0;

 protected:
 private:
};

}  // namespace planning