#include "coordinate_task.h"

namespace planning
{

CoordinateTask::CoordinateTask(
    const common::base::ConfNode &yaml_conf)
    : Task(yaml_conf){};

CoordinateTask::~CoordinateTask(){};

bool CoordinateTask::Init()
{
  AINFO << "CoordinateTask init";
  return true;
}
bool CoordinateTask::Run(Frame *frame)
{
  // input
  const auto &reference_line = frame->refrenceline();
  // output
  auto &car_state = *(frame->mutable_car_state());
  auto &car_state_sl = *(frame->mutable_car_state_sl());
  // process
  Coordinate::POS_to_SL(reference_line,
                        car_state,
                        car_state_sl);
  return true;
}
bool CoordinateTask::Stop() {
  return true;
}

} // namespace planning