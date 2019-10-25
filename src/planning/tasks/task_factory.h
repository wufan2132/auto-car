#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include "planning/replay/record_trajectory.h"
#include "planning/refrenceline/refrenceline_provider.h"
#include "planning/tool/interpolating_refrenceline.h"
#include "planning/trajectory/trajectory_start_point.h"
#include "planning/planner/og_planner.h"
#include "task.h"
#include "task_test.h"
namespace planning {

#define RegisterTask(object_type)                                  \
  producers_[#object_type] = [](const common::base::ConfNode& conf) -> Task* { \
    return new object_type(conf);                                  \
  };

class TaskFactory {
 public:
  using Productor = std::function<Task*(const common::base::ConfNode&)>;
  TaskFactory() {
    RegisterTask(TaskTest);
    RegisterTask(RecordTrajectory);
    RegisterTask(RefrencelineProvider);
    RegisterTask(InterpolatingRefrenceline);
    RegisterTask(TrajectoryStartPoint);
    RegisterTask(OgPlanner);
  }

  std::unique_ptr<Task> CreatObject(std::string type, const common::base::ConfNode& conf);

 private:
  std::unordered_map<std::string, Productor> producers_;
};

}  // namespace planning