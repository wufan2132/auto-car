#pragma once

#include "ros/ros.h"
#include "common/base/log.h"
#include "planning/common/frame.h"
#include "planning/common/planning_gflags.h"
#include "yaml-cpp/yaml.h"

namespace planning {

class Task {
 public:
  Task(const common::base::ConfNode& yaml_conf){};
  virtual ~Task() = default;

  virtual bool Init() = 0;
  virtual bool Run(Frame* frame) = 0;
  virtual bool Stop() = 0;
};

}  // namespace planning