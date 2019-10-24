#pragma once

#include <memory>
#include "interpolating.h"
#include "planning/tasks/task.h"

namespace planning {

class InterpolatingRefrenceline : public Task {
 public:
  InterpolatingRefrenceline(const YAML::Node& yaml_conf);
  ~InterpolatingRefrenceline();

  bool Init();
  bool Run(Frame* frame);
  bool Stop();

 private:
  bool is_ok_ = 0;
  std::unique_ptr<Interpolating> interpolating_;
};

}  // namespace planning