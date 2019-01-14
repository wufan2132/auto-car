/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include "control/trajectory_analyzer.h"

#include <algorithm>
#include <cmath>
#include <utility>

#include "math/linear_interpolation.h"
#include "math/math_utils.h"
#include "math/search.h"

namespace math = common::math;

namespace control {
namespace {

// Squared distance from the point to (x, y).
double PointDistanceSquare(const car_msgs::trajectory_point &point, const double x,
                           const double y) {
  const double dx = point.x - x;
  const double dy = point.y - y;
  return dx * dx + dy * dy;
}

car_msgs::trajectory_point TrajectoryPointToPathPoint(const car_msgs::trajectory_point &point) {
  // if (point.has_path_point()) {
  //   return point.path_point();
  // } else {
  //   return PathPoint();
  // }
  return point;
}

}  // namespace

TrajectoryAnalyzer::TrajectoryAnalyzer(
    const car_msgs::trajectory *planning_published_trajectory) {
  header_time_ = planning_published_trajectory->absolute_time;
  seq_num_ = planning_published_trajectory->header.seq;

  for (int i = 0; i < planning_published_trajectory->trajectory_path.size();
       ++i) {
    trajectory_points_.push_back(
        planning_published_trajectory->trajectory_path.at(i));
  }
}

car_msgs::trajectory_point TrajectoryAnalyzer::QueryMatchedPathPoint(const double x,
                                                    const double y) const {
  //CHECK_GT(trajectory_points_.size(), 0);

  double d_min = PointDistanceSquare(trajectory_points_.front(), x, y);
  size_t index_min = 0;

  for (size_t i = 1; i < trajectory_points_.size(); ++i) {
    double d_temp = PointDistanceSquare(trajectory_points_[i], x, y);
    if (d_temp < d_min) {
      d_min = d_temp;
      index_min = i;
    }
  }

  size_t index_start = index_min == 0 ? index_min : index_min - 1;
  size_t index_end =
      index_min + 1 == trajectory_points_.size() ? index_min : index_min + 1;

  const double kEpsilon = 0.001;
  if (index_start == index_end ||
      std::fabs(trajectory_points_[index_start].s -
                trajectory_points_[index_end].s) <= kEpsilon) {
    return TrajectoryPointToPathPoint(trajectory_points_[index_start]);
  }

  return FindMinDistancePoint(trajectory_points_[index_start],
                              trajectory_points_[index_end], x, y);
}

// reference: Optimal trajectory generation for dynamic street scenarios in a
// Frenét Frame,
// Moritz Werling, Julius Ziegler, Sören Kammel and Sebastian Thrun, ICRA 2010
// similar to the method in this paper without the assumption the "normal"
// vector
// (from vehicle position to ref_point position) and reference heading are
// perpendicular.
void TrajectoryAnalyzer::ToTrajectoryFrame(const double x, const double y,
                                           const double theta, const double v,
                                           const car_msgs::trajectory_point &ref_point,
                                           double *ptr_s, double *ptr_s_dot,
                                           double *ptr_d,
                                           double *ptr_d_dot) const {
  double dx = x - ref_point.x;
  double dy = y - ref_point.y;

  double cos_ref_theta = std::cos(ref_point.theta);
  double sin_ref_theta = std::sin(ref_point.theta);

  // the sin of diff angle between vector (cos_ref_theta, sin_ref_theta) and
  // (dx, dy)
  double cross_rd_nd = cos_ref_theta * dy - sin_ref_theta * dx;
  *ptr_d = cross_rd_nd;

  // the cos of diff angle between vector (cos_ref_theta, sin_ref_theta) and
  // (dx, dy)
  double dot_rd_nd = dx * cos_ref_theta + dy * sin_ref_theta;
  *ptr_s = ref_point.s + dot_rd_nd;

  double delta_theta = theta - ref_point.theta;
  double cos_delta_theta = std::cos(delta_theta);
  double sin_delta_theta = std::sin(delta_theta);

  *ptr_d_dot = v * sin_delta_theta;

  double one_minus_kappa_r_d = 1 - ref_point.kappa * (*ptr_d);
  if (one_minus_kappa_r_d <= 0.0) {
    // AERROR << "TrajectoryAnalyzer::ToTrajectoryFrame "
    //           "found fatal reference and actual difference. "
    //           "Control output might be unstable:"
    //        << " ref_point.kappa:" << ref_point.kappa()
    //        << " ref_point.x:" << ref_point.x()
    //        << " ref_point.y:" << ref_point.y() << " car x:" << x
    //        << " car y:" << y << " *ptr_d:" << *ptr_d
    //        << " one_minus_kappa_r_d:" << one_minus_kappa_r_d;
    // currently set to a small value to avoid control crash.
    one_minus_kappa_r_d = 0.01;
  }

  *ptr_s_dot = v * cos_delta_theta / one_minus_kappa_r_d;
}

car_msgs::trajectory_point TrajectoryAnalyzer::QueryNearestPointByAbsoluteTime(
    const double t) const {
  return QueryNearestPointByRelativeTime(t - header_time_);
}

car_msgs::trajectory_point TrajectoryAnalyzer::QueryNearestPointByRelativeTime(
    const double t) const {
  auto func_comp = [](const car_msgs::trajectory_point &point,
                      const double relative_time) {
    return point.relative_time < relative_time;
  };

  auto it_low = std::lower_bound(trajectory_points_.begin(),
                                 trajectory_points_.end(), t, func_comp);

  if (it_low == trajectory_points_.begin()) {
    return trajectory_points_.front();
  }

  if (it_low == trajectory_points_.end()) {
    return trajectory_points_.back();
  }

  auto it_lower = it_low - 1;
  if (it_low->relative_time - t < t - it_lower->relative_time) {
    return *it_low;
  }
  return *it_lower;
}

car_msgs::trajectory_point TrajectoryAnalyzer::QueryNearestPointByPosition(
    const double x, const double y) const {
  //CHECK_GT(trajectory_points_.size(), 0);

  double d_min = PointDistanceSquare(trajectory_points_.front(), x, y);
  size_t index_min = 0;

  for (size_t i = 1; i < trajectory_points_.size(); ++i) {
    double d_temp = PointDistanceSquare(trajectory_points_[i], x, y);
    if (d_temp < d_min) {
      d_min = d_temp;
      index_min = i;
    }
  }
  return trajectory_points_[index_min];
}

const std::vector<car_msgs::trajectory_point> &TrajectoryAnalyzer::trajectory_points()
    const {
  return trajectory_points_;
}

car_msgs::trajectory_point TrajectoryAnalyzer::FindMinDistancePoint(const car_msgs::trajectory_point &p0,
                                                   const car_msgs::trajectory_point &p1,
                                                   const double x,
                                                   const double y) const {
  // given the fact that the discretized trajectory is dense enough,
  // we assume linear trajectory between consecutive trajectory points.
  auto dist_square = [&p0, &p1, &x, &y](const double s) {
    double px = math::lerp(p0.x, p0.s,
                           p1.x, p1.s, s);
    double py = math::lerp(p0.y, p0.s,
                           p1.y, p1.s, s);
    double dx = px - x;
    double dy = py - y;
    return dx * dx + dy * dy;
  };

  car_msgs::trajectory_point p = p0;
  double s = math::GoldenSectionSearch(dist_square, p0.s, p1.s);
  p.s = s;
  p.x = math::lerp(p0.x, p0.s,
                     p1.x, p1.s, s);
  p.y = math::lerp(p0.y, p0.s,
                     p1.y, p1.s, s);
  p.theta = math::slerp(p0.theta, p0.s,
                          p1.theta, p1.s, s);
  // approximate the curvature at the intermediate point
  p.kappa = math::lerp(p0.kappa, p0.s,
                         p1.kappa, p1.s, s);
  return p;
}

}  // namespace control
