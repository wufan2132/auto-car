
#pragma once

#include <string>

#include "common/base/global_gflags/global_gflags.h"
#include "yaml-cpp/yaml.h"

namespace common {
namespace base {

class FileTool {
 public:
  static std::string ToAbsDir(std::string path);
  static YAML::Node LoadFile(std::string path);
};

}  // namespace common
}  // namespace autocar
