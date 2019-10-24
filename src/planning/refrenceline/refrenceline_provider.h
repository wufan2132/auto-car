#pragma once

#include <Eigen/Dense>
#include <atomic>
#include <thread>
#include "planning/common/frame.h"
#include "planning/map/A_star.h"
#include "planning/map/Image.h"
#include "planning/map/map_convert.h"
#include "planning/map/road.h"
#include "planning/tasks/task.h"

namespace planning {

class RefrencelineProvider : public Task {
 public:
  RefrencelineProvider(const YAML::Node& yaml_conf);
  ~RefrencelineProvider();

  bool Init();
  bool Run(Frame* frame);
  bool Stop();

 private:
  void GetRefrencelineFromMap(car_msgs::trajectory* refrenceline);
  void GetRefrencelineFromCSV(car_msgs::trajectory* refrenceline);
  // conf
  class Conf {
   public:
    std::string mode;
    // from csv
    std::string csv_path;
    // from map
    double start_point_x;
    double start_point_y;
    double end_point_x;
    double end_point_y;
    std::string origin_image_path;
    std::string output_image_path;
    int origin_road_width;
    double scale;
    double spacing;
    int smooth_order;
  };
  Conf conf_;
  std::atomic_int is_ready_;
  bool has_refrenceline_task_ = true;
  //模块
  std::unique_ptr<std::thread> work_thread_;
  Astar* astar;
  MapConvert* map_convert;
};
}  // namespace planning