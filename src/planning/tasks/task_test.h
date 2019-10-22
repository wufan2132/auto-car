#pragma once

#include "planning/tasks/task.h"

namespace planning {

class TaskTest : public Task {
 public:
  TaskTest(const YAML::Node& yaml_conf) : Task(yaml_conf) {
    AINFO << "TaskTest::TaskTest()";
  };
  ~TaskTest() = default;

  void Init() { AINFO << "TaskTest::Init()"; };
  void Run(Frame* frame) { AINFO << "TaskTest::Run()"; }
  void Stop(){};
};

}  // namespace planning