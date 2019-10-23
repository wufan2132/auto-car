
#pragma once

#include "yaml-cpp/yaml.h"

namespace planning {
// 数据帧
class Frame {
 public:
  Frame();
  ~Frame();
  void Init();
  //
  const car_msgs::trajectory_point& car_state(){
      return car_state_;
  }

 private:
  // car state
  car_msgs::trajectory_point car_state_;
};

}  // namespace planning