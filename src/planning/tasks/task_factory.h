#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include "task.h"
#include "task_test.h"
namespace planning {

#define RegisterTask(object_type)                               \
  producers_["#object_type#"] = [](YAML::Node& conf) -> Task* { \
    return new object_type(conf);                               \
  };

class TaskFactory {
 public:
  using Productor = std::function<Task*(YAML::Node&)>;
  TaskFactory() {
    RegisterTask(TaskTest);
    // RegisterTask(TaskTest);
  }

  std::unique_ptr<Task> CreatObject(std::string type, YAML::Node conf) {
    auto id_iter = producers_.find(type);
    if (id_iter != producers_.end()) {
      return std::unique_ptr<Task>((id_iter->second)(conf));
    }
    return nullptr;
  }

 private:
  std::unordered_map<std::string, Productor> producers_;
};

}  // namespace planning