#include "planning.h"
#include "common/base/file_tool/conf_node.h"

namespace planning {

using common::base::ConfNode;
using common::util::Activator;

Planning::Planning(const common::base::ConfNode& planning_conf) {
  TaskFactory task_factory;
  for (const auto& node : planning_conf["task_list"]) {
    const string& task_name = node.as<string>();
    task_list_.emplace_back(task_factory.CreatObject(task_name, planning_conf));
    CHECK(task_list_.back().get()) << "unknow task name:" << task_name;
    AINFO << "load task:" << task_name;
  }
}

void Planning::Init(ros::NodeHandle* node_handle) {
  //订阅
  localization_subscriber_ =
      node_handle->subscribe(FLAGS_chassis_localization_topic, 1,
                             &Planning::LocalizationCallback, this);
  chassis_subscriber_ = node_handle->subscribe(
      FLAGS_chassis_car_state_topic, 1, &Planning::ChassisCallback, this);
  obstacle_subscriber_ = node_handle->subscribe(
      "obstacle_topic", 1, &Planning::ObstacleCallback, this);
  //发布
  refrenceline_publisher_ = node_handle->advertise<car_msgs::trajectory>(
      FLAGS_planning_refrenceline_topic, 1000);
  trajectory_publisher_ = node_handle->advertise<car_msgs::trajectory>(
      FLAGS_planning_trajectory_topic, 1000);
  // timer
  timer_ = node_handle->createTimer(ros::Duration(conf_.period),
                                    &Planning::OnTimer, this);
  //初始化其他模块
  // frame
  frame_ = std::make_unique<Frame>();
  frame_->Init();
  for (auto& task : task_list_) {
    task->Init();
  }
  activator_ = std::make_unique<Activator>(2);
}

//读节点数据
void Planning::LocalizationCallback(
    const car_msgs::localization& localization) {
  *(frame_->mutable_car_localization()) = localization;
  frame_->mutable_car_state()->x = localization.position.x;
  frame_->mutable_car_state()->y = localization.position.y;
  frame_->mutable_car_state()->z = localization.position.z;
  frame_->mutable_car_state()->theta = localization.angle.z;
  activator_->Activate("LocalizationCallback");
}

void Planning::ChassisCallback(const car_msgs::chassis& chassis) {
  *(frame_->mutable_car_chassis()) = chassis;
  static u_int64_t cnt = 1;
  frame_->mutable_car_state()->speed = chassis.speed.x;
  frame_->mutable_car_state()->accel = chassis.acc.x;
  frame_->mutable_car_state()->header.seq = cnt++;
  activator_->Activate("ChassisCallback");
}

void Planning::ObstacleCallback(
    const car_msgs::base_obstacle_list& obstacle_msg) {
  //   obstaclelist->refresh(obstacle_msg);
}

void Planning::OnTimer(const ros::TimerEvent&) { this->RunOnce(); }

void Planning::RunOnce(void) {
  if (!activator_->State()) {
    // not ready
    return;
  }
  //运行task
  for (auto& task : task_list_) {
    if (!task->Run(frame_.get())) {
      break;
    }
  }
  //发布
  if (!frame_->refrenceline_is_ready() &&
      frame_->refrenceline().total_path_length > 0) {
    refrenceline_publisher_.publish(frame_->refrenceline());
    frame_->set_refrenceline_is_ready(true);
    AINFO << "published refrenceline.";
  }
  if (frame_->trajectory_out_is_ready()) {
    trajectory_publisher_.publish(frame_->trajectory_out());
    AINFO << "published trajectory.";
  }
}

}  // namespace planning