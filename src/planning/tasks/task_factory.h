#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include "planning/replay/record_trajectory.h"
#include "task.h"
#include "task_test.h"
namespace planning {

#define RegisterTask(object_type)                            \
  producers_[#object_type] = [](const YAML::Node& conf) -> Task* { \
    return new object_type(conf);                            \
  };

class TaskFactory {
 public:
  using Productor = std::function<Task*(const YAML::Node&)>;
  TaskFactory() {
    RegisterTask(TaskTest);
    RegisterTask(RecordTrajectory);
  }

  std::unique_ptr<Task> CreatObject(std::string type, const YAML::Node& conf);
 private:
  std::unordered_map<std::string, Productor> producers_;
};

}  // namespace planning