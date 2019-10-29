#pragma once

#include <memory>
#include "planning//coordinate/coordinate.h"
#include "planning/tasks/task.h"

namespace planning {

class CoordinateTask : public Task {
 public:
  CoordinateTask(const common::base::ConfNode& yaml_conf);
  ~CoordinateTask();

  bool Init();
  bool Run(Frame* frame);
  bool Stop();
};

}  // namespace planning