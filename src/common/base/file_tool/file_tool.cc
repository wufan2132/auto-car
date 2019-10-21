

#include "file_tool.h"
#include <glog/logging.h>

namespace common {
namespace base {

std::string FileTool::ToAbsDir(std::string path) {
  if (path != "" && path[0] == '/') {
    return path;
  }
  return FLAGS_base_dir + '/' + path;
}

YAML::Node FileTool::LoadFile(std::string path) {
  try {
    return YAML::LoadFile(path);
  } catch(std::exception e) {
    CHECK(NULL) << "yaml load file failed, can not find file at: " << path;
    return YAML::Node();
  }
}

}  // namespace common
}  // namespace autocar