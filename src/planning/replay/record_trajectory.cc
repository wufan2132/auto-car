#include "record_trajectory.h"

namespace planning {

RecordTrajectory::RecordTrajectory(const common::base::ConfNode& yaml_conf)
    : Task(yaml_conf) {
  replay_ = std::make_unique<Replay>(FLAGS_record_trajectory_path, "write");
  const auto& conf_node = yaml_conf["record_trajectory"];
  if (conf_node.IsDefined("record_step")) {
    record_step_ = conf_node["record_step"].as<double>();
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
  // intput
  const auto& car_state = frame->car_state();
  // output
  // process
  double d2 = (car_state.x - last_state_.x) * (car_state.x - last_state_.x) +
              (car_state.y - last_state_.y) * (car_state.y - last_state_.y);
  if (d2 >= record_step_ * record_step_) {
    replay_->SaveOnce(car_state);
    last_state_ = car_state;
  }
  return true;
}

bool RecordTrajectory::Stop() { return true; }

}  // namespace planning
