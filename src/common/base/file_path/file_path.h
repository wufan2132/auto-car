
#pragma once

#include <string>

#include "common/base/global_gflags/global_gflags.h"

namespace autocar {

namespace common {

class FilePathTool {
 public:
  static std::string ToAbsDir(std::string path) {
    if (path != "" && path[0] == '/') {
      return path;
    }
    return FLAGS_base_dir + '/' + path;
  }
};

}  // namespace common
}  // namespace autocar
