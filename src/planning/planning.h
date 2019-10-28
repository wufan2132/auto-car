#pragma once

#include <ros/ros.h>
#include <Eigen/Dense>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "car_msgs/base_obstacle.h"
#include "car_msgs/base_obstacle_list.h"
#include "car_msgs/chassis.h"
#include "car_msgs/localization.h"
#include "car_msgs/trajectory.h"
#include "car_msgs/trajectory_point.h"
#include "common/base/global_gflags/global_gflags.h"
#include "nav_msgs/Odometry.h"
#include "common/util/activator.h"
#include "planning/common/frame.h"
#include "planning/tasks/task_factory.h"

namespace planning {

class Planning {
 public:
  Planning(const common::base::ConfNode& planning_conf);

  void Init(ros::NodeHandle* node_handle);

  void RunOnce();

  void OnTimer(const ros::TimerEvent& timer_event_);

  void LocalizationCallback(const car_msgs::localization& localization);

  void ChassisCallback(const car_msgs::chassis& chassis);

  void ObstacleCallback(const car_msgs::base_obstacle_list& obstacle_msg);

  car_msgs::trajectory_point generate_trajectory_point(
      const car_msgs::localization& localization,
      const car_msgs::chassis& chassis);
  // ros模块
  ros::Timer timer_;
  ros::Subscriber localization_subscriber_;
  ros::Subscriber chassis_subscriber_;
  ros::Subscriber obstacle_subscriber_;
  ros::Publisher trajectory_publisher_;
  ros::Publisher refrenceline_publisher_;
  //配置参数
  class Conf {
   public:
    std::string mode;
    double period;
    std::string refrenceline_source;
    double wait_time;
    std::string trajectory_dir;
    int sampling_period;
  };
  Conf conf_;
  //模块
  std::vector<std::unique_ptr<Task>> task_list_;
  std::unique_ptr<Frame> frame_;
  std::unique_ptr<common::util::Activator> activator_;
  //   Planner* planner;
  //   Refrenceline_provider* rprovider;
  //   ObstacleList* obstaclelist;
};

}  // namespace planning