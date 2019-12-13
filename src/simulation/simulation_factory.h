#pragma once

#include <string>
#include <unordered_map>
#include "gazebo_simulation.h"

namespace simulation {

#define RegisterSimulation(name, object_type)              \
  producers_[name] = [](const YAML::Node& conf) -> Simulation* {  \
    return new object_type(conf);                       \
  };

class SimulationFactory {
 public:
  using Productor = std::function<Simulation*(const YAML::Node&)>;
  SimulationFactory() {
    // RegisterSimulation("gazebo", GazeboSimulation);
    RegisterSimulation("gazebo", GazeboSimulation);
  }

  std::unique_ptr<Simulation> CreatObject(std::string type, const YAML::Node& conf) {
    auto id_iter = producers_.find(type);
    if (id_iter != producers_.end()) {
      return std::unique_ptr<Simulation>((id_iter->second)(conf));
    }
    return nullptr;
  }

 private:
  std::unordered_map<std::string, Productor> producers_;
};

}  // namespace simulation