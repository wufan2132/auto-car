#include "trajectory_start_point.h"

namespace planning {

using namespace Eigen;

TrajectoryStartPoint::TrajectoryStartPoint(const common::base::ConfNode& yaml_conf)
    : Task(yaml_conf) {
  const auto& tsp_conf = yaml_conf["trajectory_start_point"];
  conf_.keep_t = tsp_conf["keep_t"].as<double>();
  conf_.available_l = tsp_conf["available_l"].as<double>();
};
TrajectoryStartPoint::~TrajectoryStartPoint(){};

bool TrajectoryStartPoint::Init() { AINFO << "TrajectoryStartPoint init"; };

bool TrajectoryStartPoint::Run(Frame* frame) {
  // input
  const auto& status_sl = frame->car_state_sl();
  const auto& car_state = frame->car_state();
  // output
  auto& planning_start_point = *(frame->mutable_planning_start_point());
  auto& trajectory_now = *(frame->mutable_trajectory_out());
  // process
  /*********************************************/
  //重新从车的当前位置开始规划的条件
  // 1.预测的时间为0，设定成这样
  // 2.上次轨迹丢失
  // 3.车体偏离预设轨迹较远
  if (conf_.keep_t == 0 || trajectory_now.total_path_length < 5 ||
      IsReplanning(car_state, trajectory_now, conf_.available_l)) {
    //重置标志位
    is_replanning_ = 1;
    //设置起点为车的当前坐标
    planning_start_point = status_sl;
    planning_start_point.start_pos = 0;
    planning_start_point.t = 0;
    last_s_ = planning_start_point.s;
    last_keep_len_ = 0;
    AINFO << "get_start_point: replanning!";
    return true;
  }

  int start_index = 0;
  while (start_index < trajectory_now.total_path_length - 1 &&
         status_sl.s - trajectory_now.trajectory_path[start_index + 1].s > 0)
    start_index++;
  float T0 = trajectory_now.trajectory_path[start_index].relative_time;
  VectorXf T(1);
  int end_index = 0;
  //第一次运行时间是没有偏差的
  if (is_replanning_) {
    T << (T0 + conf_.keep_t);
    is_replanning_ = 0;
    while (end_index < trajectory_sl_.size() &&
           T(0) > trajectory_sl_[end_index].t)
      end_index++;
  } else {
    //预测一秒后的，本来这里要加上1，但由于后面相对时间是从0开始算的，已经加了1，
    T << T0;
    while (end_index < trajectory_sl_.size() &&
           T(0) > trajectory_sl_[end_index].t)
      end_index++;
    end_index += last_keep_len_;
  }
  int len1 = end_index - start_index;

  //更新前面保留的点
  for (int i = 0; i < len1; i++) {
    trajectory_now.trajectory_path[i] =
        trajectory_now.trajectory_path[i + start_index];
    trajectory_now.trajectory_path[i].relative_time -= T0;
    trajectory_now.trajectory_path[i].header.seq = i + 1;
  }
  ////////////////////////////////////////////////
  planning_start_point = trajectory_sl_[end_index - last_keep_len_];
  planning_start_point.start_pos = len1;
  planning_start_point.t = conf_.keep_t;
  last_keep_len_ = len1;
  return true;
}

bool TrajectoryStartPoint::Stop() { return true; };

bool TrajectoryStartPoint::IsReplanning(
    const car_msgs::trajectory_point& car_status,
    const car_msgs::trajectory& trajectory_now, const double available_l) {
  int index = 0;
  while (index < trajectory_now.total_path_length - 1 &&
         car_status.s - trajectory_now.trajectory_path[index].s > 0)
    index++;
  double distance =
      (car_status.x - trajectory_now.trajectory_path[index].x) *
          (car_status.x - trajectory_now.trajectory_path[index].x) +
      (car_status.y - trajectory_now.trajectory_path[index].y) *
          (car_status.y - trajectory_now.trajectory_path[index].y);
  if (distance > available_l * available_l)
    return true;
  else
    return false;
}

}  // namespace planning