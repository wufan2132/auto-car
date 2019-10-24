#pragma once

#include "planning/tasks/task.h"

namespace planning {

class TaskTest : public Task {
 public:
  TaskTest(const YAML::Node& yaml_conf) : Task(yaml_conf) {
    AINFO << "TaskTest::TaskTest()";
  };
  ~TaskTest() = default;

  bool Init() {
    AINFO << "TaskTest::Init()";
    return true;
  };
  bool Run(Frame* frame) {
    AINFO << "TaskTest::Run()";
    return true;
  }
  bool Stop() { return true; };
};

}  // namespace planning