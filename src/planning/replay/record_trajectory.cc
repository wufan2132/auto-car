#include "record_trajectory.h"

namespace planning {

RecordTrajectory::RecordTrajectory(const YAML::Node& yaml_conf) {
  // TODO add path
  replay_ = std::make_unique<replay>("path", "write");
}

RecordTrajectory::~RecordTrajectory() {

}

void RecordTrajectory::Init() { replay_.reset(); }

void RecordTrajectory::Run(Frame* frame) {}

void RecordTrajectory::Stop() {}

}  // namespace planning
