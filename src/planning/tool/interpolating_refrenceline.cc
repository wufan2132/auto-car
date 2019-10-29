#include "interpolating_refrenceline.h"

namespace planning {

InterpolatingRefrenceline::InterpolatingRefrenceline(
    const common::base::ConfNode& yaml_conf)
    : Task(yaml_conf) {
  interpolating_ = std::make_unique<Interpolating>(yaml_conf["interpolating"]);
}
InterpolatingRefrenceline::~InterpolatingRefrenceline(){};

bool InterpolatingRefrenceline::Init() {
  AINFO << "InterpolatingRefrenceline init";
}
bool InterpolatingRefrenceline::Run(Frame* frame) {
  // input
  const auto& raw_refrenceline = frame->raw_refrenceline();
  // output
  auto* refrenceline = frame->mutable_refrenceline();
  auto* analytic_refrenceline = frame->mutable_analytic_refrenceline();
  // process
  if (frame->refrenceline_is_ready()){
    return true;
  }
  interpolating_->process(raw_refrenceline, refrenceline, analytic_refrenceline);
  return true;
}
bool InterpolatingRefrenceline::Stop() {}
}  // namespace planning