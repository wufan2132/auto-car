#include "interpolating_refrenceline.h"

namespace planning {

InterpolatingRefrenceline::InterpolatingRefrenceline(
    const common::base::ConfNode& yaml_conf)
    : Task(yaml_conf) {
  interpolating_ = std::make_unique<Interpolating>(yaml_conf["Interpolating"]);
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
  auto* analytic_refrenceline_ = frame->mutable_analytic_refrenceline();
  // process
  analytic_refrenceline_ =
      interpolating_->process(raw_refrenceline, refrenceline);
}
bool InterpolatingRefrenceline::Stop() {}
}  // namespace planning