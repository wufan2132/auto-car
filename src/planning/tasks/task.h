#pragma once

#include "common/base/log.h"
#include "planning/common/frame.h"
#include "planning/common/planning_gflags.h"
#include "yaml-cpp/yaml.h"

namespace planning {

class Task {
 public:
  Task(const YAML::Node& yaml_conf){};
  virtual ~Task() = default;

  virtual void Init() = 0;
  virtual void Run(Frame* frame) = 0;
  virtual void Stop() = 0;
};

}  // namespace planning