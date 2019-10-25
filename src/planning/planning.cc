#include "planning.h"
#include "common/base/file_tool/conf_node.h"

namespace planning {
using common::base::ConfNode;
using namespace std;

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
}

//读节点数据
void Planning::LocalizationCallback(
    const car_msgs::localization& localization) {
  //   car_localization = localization;
}

void Planning::ChassisCallback(const car_msgs::chassis& chassis) {
  //   if (STATE == 0) STATE = 1;
  //   car_chassis = chassis;
  //   car_status = generate_trajectory_point(car_localization, car_chassis);
  //   if (conf.mode == "write") {
  //     static replay replayer(conf.trajectory_dir, "write");
  //     if (car_localization.header.seq > 0) {
  //       replayer.saveOnce(car_status, conf.sampling_period);
  //     }
  //   }
}

void Planning::ObstacleCallback(
    const car_msgs::base_obstacle_list& obstacle_msg) {
  //   obstaclelist->refresh(obstacle_msg);
}

car_msgs::trajectory_point Planning::generate_trajectory_point(
    const car_msgs::localization& localization,
    const car_msgs::chassis& chassis) {
  //   static int count = 0;
  //   count++;
  car_msgs::trajectory_point point;
  //   //生成 point
  //   point.header.seq = count;
  //   point.x = localization.position.x;
  //   point.y = localization.position.y;
  //   point.z = localization.position.z;
  //   point.theta = localization.angle.z;
  //   point.speed = chassis.speed.x;
  //   point.accel = chassis.acc.x;
  return point;
}

void Planning::OnTimer(const ros::TimerEvent&) { this->RunOnce(); }

void Planning::RunOnce(void) {
  //运行task
  for (auto& task : task_list_) {
    if (!task->Run(frame_.get())) {
      break;
    }
  }
  //发布
  if (frame_->refrenceline_is_ready()) {
    refrenceline_publisher_.publish(frame_->refrenceline());
    AINFO << "published refrenceline.";
  }
  if (frame_->trajectory_out_is_ready()) {
    trajectory_publisher_.publish(frame_->trajectory_out());
    AINFO << "published trajectory.";
  }
}

}  // namespace planning