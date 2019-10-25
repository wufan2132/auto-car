#include "record_trajectory.h"

namespace planning {

RecordTrajectory::RecordTrajectory(const common::base::ConfNode& yaml_conf)
    : Task(yaml_conf) {
  replay_ = std::make_unique<Replay>(FLAGS_record_trajectory_path, "write");
  if (yaml_conf["record_step"].IsDefined()) {
    record_step_ = yaml_conf["record_step"].as<int>();
  }
}

RecordTrajectory::~RecordTrajectory() {}

bool RecordTrajectory::Init() {
  replay_->Reset();
  AINFO << "RecordTrajectory::Init";
  return true;
}

bool RecordTrajectory::Run(Frame* frame) {
  CHECK_NOTNULL(frame);
  CHECK_NOTNULL(replay_);
  //intput
  const auto& car_state = frame->car_state();
  //output
  //process
  step_count_++;
  if (step_count_ >= record_step_) {
    step_count_ = 0;
    replay_->SaveOnce(car_state);
  }
  return true;
}

bool RecordTrajectory::Stop() { return true; }

}  // namespace planning
