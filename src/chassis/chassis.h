#pragma once

#include <string>
#include "yaml-cpp/yaml.h"

namespace chassis {

class Chassis {
 public:
  Chassis(YAML::Node yaml_conf) = default;
  virtual ~Chassis() = default;

  virtual void Init() = 0;
  virtual void RunOnce() = 0;
  virtual void Stop() = 0;

 protected:
  std::string mode() { return mode; };

 private:
  std::string mode;
};

}  // namespace chassis