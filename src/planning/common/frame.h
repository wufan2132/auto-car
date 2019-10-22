
#pragma once

#include "yaml-cpp/yaml.h"

namespace planning {
// 数据帧
class Frame {
 public:
  Frame();
  ~Frame();
  void Init();
};

}  // namespace planning