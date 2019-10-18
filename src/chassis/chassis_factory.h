#pragma once

#include <string>
#include <unordered_map>
#include "gazebo_chassis.h"

namespace chassis {

class ChassisFactory {
 public:
  using Productor = std::function<Chassis*(YAML::Node& conf)>;
  ChassisFactory() {
    //
    RegisterChassis("gazebo", GazeboChassis);
  };

  std::unique_ptr<Chassis> CreatObject(std::string type, YAML::Node& conf) {
    auto id_iter = producers_.find(type);
    if (id_iter != producers_.end()) {
      return std::unique_ptr<Chassis>((id_iter->second)(conf));
    }
    return nullptr;
  }

 private:
  std::unordered_map<std::string, Productor> producers_;
};

#define RegisterChassis(name, object_type)              \
  producers_[name] = [](YAML::Node& conf) -> Chassis* { \
    return new object_type(conf);                       \
  };

}  // namespace chassis