
#include "global_gflags.h"

DEFINE_string(base_dir, "/autocar", "program base dir");

DEFINE_string(system_run_mode, "gazebo", "real or gazebo");

DEFINE_string(car_name, "none", "car name");

/**************************topic*************************/
//chassis
DEFINE_string(chassis_localization_topic, "/autocar/chassis/localization",
              "publish topic name");
DEFINE_string(chassis_car_state_topic, "/autocar/chassis/car_state",
              "publish topic name");
//gazebo
DEFINE_string(gazebo_Odometry_topic, "base_pose_ground_truth",
              "publish topic name");
DEFINE_string(gazebo_imu_topic, "imu", "publish topic name");
//planning
DEFINE_string(planning_refrenceline_topic, "/autocar/planning/refrenceline",
              "publish topic name");
DEFINE_string(planning_trajectory_topic, "/autocar/planning/trajectory",
              "publish topic name");
//control
DEFINE_string(control_controlcmd_topic, "prius",
              "publish topic name");
DEFINE_string(control_debug_topic, "/autocar/control/debug",
              "publish topic name");
//other
DEFINE_string(param_topic, "param_topic",
              "publish topic name");