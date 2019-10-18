#pragma once

#include <string>
#include <ros/ros.h>
#include "yaml-cpp/yaml.h"
#include "common/base/log.h"

namespace chassis {

class Chassis {
 public:
  Chassis(YAML::Node yaml_conf) {};
  virtual ~Chassis() = default;

  virtual void Init(ros::NodeHandle *node_handle) = 0;
  virtual void RunOnce() = 0;
  virtual void Stop() = 0;

 protected:
  std::string mode() { return mode_; };

 private:
  std::string mode_;
};

}  // namespace chassis