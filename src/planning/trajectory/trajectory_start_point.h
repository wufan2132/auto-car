#pragma once

#include "planning/coordinate/car_state_sl.h"
#include "planning/tasks/task.h"

namespace planning {

class TrajectoryStartPoint : public Task {
 public:
  TrajectoryStartPoint(const common::base::ConfNode& yaml_conf) ;
  ~TrajectoryStartPoint();

  bool Init();
  bool Run(Frame* frame);
  bool Stop();

  bool IsReplanning(const car_msgs::trajectory_point& car_status,
                    const car_msgs::trajectory& trajectory_now,
                    const double available_l);

 private:
  class Conf {
  public:
    double keep_t;
    double available_l;
  };
  Conf conf_;
  //
  bool is_replanning_;
  int last_keep_len_;
  double last_s_;
};

}  // namespace planning