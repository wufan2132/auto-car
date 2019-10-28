#include "planning/planner/og_planner.h"
#include "planning/trajectory/trajectory_generation.h"
namespace planning
{

using namespace Eigen;

OgPlanner::OgPlanner(const common::base::ConfNode &yaml_conf) : Planner(yaml_conf)
{
  const auto &og_conf = yaml_conf["og_planner"];
  conf_.step_t = og_conf["step_t"].as<double>();
  conf_.planning_t = og_conf["planning_t"].as<double>();
  conf_.aim_speed = og_conf["aim_speed"].as<double>();
  conf_.speed_correction = og_conf["speed_correction"].as<double>();
  conf_.speed_min_limit = og_conf["speed_min_limit"].as<double>();
}

OgPlanner::~OgPlanner() {}

bool OgPlanner::Init() {}
bool OgPlanner::Stop() {}

bool OgPlanner::Run(Frame *frame)
{
  // input
  const auto &car_status = frame->car_state();
  const auto &status_sl = frame->car_state_sl();
  const auto &analytic_refrenceline = frame->analytic_refrenceline();
  const auto &refrenceline = frame->refrenceline();
  const auto &start_sl = frame->planning_start_point();
  // output
  auto &trajectory_now = *(frame->mutable_trajectory_out());
  // process
  static int count = 0;
  count++;
  /***************速度修正-测试版*******************/
  //设置终点，终点只给定目标速度，其余参数为0
  CarStateSL end_sl;
  double max_kappa = 0;
  for (int i = 0; i < trajectory_now.trajectory_path.size(); i++)
    max_kappa =
        std::max(max_kappa, abs(trajectory_now.trajectory_path[i].kappa));
  max_kappa = conf_.speed_correction * conf_.aim_speed * max_kappa;
  //最多降到0.3
  end_sl.sv = std::max(conf_.aim_speed * conf_.speed_min_limit,
                       conf_.aim_speed - max_kappa);
  // AINFO<<"aim_speed: "<< end_sl.sv ;
  /*********************************************/

  path_planning(start_sl, end_sl, conf_.planning_t - start_sl.t,
                analytic_refrenceline, trajectory_now);
  for (int i = start_sl.start_pos; i < trajectory_now.total_path_length; i++)
    trajectory_now.trajectory_path[i].relative_time += start_sl.t;
  /************debug 1***********/
  // for(int i=0;i<len;i++)
  // AINFO<<
  // trajectory_now.trajectory_path[start_index+i].header.seq<<","<<
  // trajectory_now.trajectory_path[start_index+i].x<<","<<
  // trajectory_now.trajectory_path[start_index+i].y<<","<<
  // trajectory_now.trajectory_path[start_index+i].theta<<","<<
  // trajectory_now.trajectory_path[start_index+i].kappa;
  /************debug 2***********/
  for (int i = 0; i < trajectory_now.total_path_length; i++)
  {
    AINFO << trajectory_now.trajectory_path[i].header.seq << "."
          << " s:" << trajectory_now.trajectory_path[i].s
          << " t:" << trajectory_now.trajectory_path[i].relative_time
          << " x:" << trajectory_now.trajectory_path[i].x
          << " y:" << trajectory_now.trajectory_path[i].y << ","
          << " theta:" << trajectory_now.trajectory_path[i].theta << ","
          << " kappa:" << trajectory_now.trajectory_path[i].kappa;
  }

  //添加header
  trajectory_now.header.seq = count;
  //保存车体参数
  last_sl_ = status_sl;
  // set_flag
  frame->set_trajectory_out_is_ready(true);
  return true;
}

void OgPlanner::path_planning(const CarStateSL &start_sl,
                              const CarStateSL &end_sl, const float planning_t,
                              const AnalyticPolynomial &analytic_refrenceline,
                              car_msgs::trajectory &trajectory_now,
                              int start_index)
{
  start_index = start_sl.start_pos;
  int len = planning_t / conf_.step_t + 1;
  if (len < 5)
    AINFO << "error: Planner::path_planning: sample error!";
  //速度规划
  QP4 = Fitting::quartic4_polynomial(start_sl.s, start_sl.sv, start_sl.sa,
                                     end_sl.sv, end_sl.sa, planning_t);
  VectorXf T = VectorXf::LinSpaced(len, 0, planning_t);
  MatrixXf S_out;
  Fitting::cal_point_quartic4(QP4, T, S_out);
  //横向位置规划
  QP5 = Fitting::quintic5_polynomial(start_sl.l, start_sl.dl, start_sl.ddl,
                                     end_sl.l, end_sl.dl, end_sl.ddl,
                                     S_out(len - 1, 0) - start_sl.s);
  VectorXf S;
  S.resizeLike(S_out.col(0));
  for (int i = 0; i < S.rows(); i++)
  {
    S(i) = S_out(i, 0) - start_sl.s;
  }
  MatrixXf L_out;
  Fitting::cal_point_quintic5(QP5, S, L_out);
  AINFO << "S_out:";
  AINFO << S_out;
  AINFO << "L_out:";
  AINFO << L_out;
  AINFO << "T:";
  AINFO << T;
  //生成轨迹
  TrajectoryGeneration::getTrajectory_from_SLT(
      S_out, L_out, T, analytic_refrenceline, trajectory_now, start_index);
}

} // namespace planning
