#pragma once

#include <Eigen/Dense>
#include <iostream>
#include "planning/Fitting.h"
#include "planning/Interpolating.h"
#include "planning/common.h"
#include "planning/map/A_star.h"
#include "planning/map/Image.h"
#include "planning/map/map_convert.h"
#include "planning/map/road.h"
#include "planning/tasks/task.h"

class RefrencelineProvider : public Task {
 public:
  RefrencelineProvider(const YAML::Node& yaml_conf);
  ~RefrencelineProvider();

  void Init();
  void Run(Frame* frame);
  void Stop();

 private:
  // conf
  class Conf {
   public:
    double start_point_x;
    double start_point_y;
    double end_point_x;
    double end_point_y;
    std::string origin_image_dir;
    std::string output_image_dir;
    int origin_road_width;
    double scale;
    double spacing;
    int smooth_order;
  };
  Conf conf_;
  //模块
  Astar* astar;
  MapConvert* map_convert;
};