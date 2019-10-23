#pragma once

#include <memory>
#include "planning/replay/replay.h"
#include "planning/tasks/task.h"
namespace planning {

class RecordTrajectory : public Task {
 public:
  RecordTrajectory(const YAML::Node& yaml_conf){};
  ~RecordTrajectory() = default;

  void Init();
  void Run(Frame* frame);
  void Stop();

 private:
  std::unique_ptr<replay> replay_;
};

}  // namespace planning