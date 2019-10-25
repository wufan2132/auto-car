
#pragma once

#include <string>
#include "yaml-cpp/yaml.h"

namespace common {
namespace base {

class ConfNode : public YAML::Node {
 public:
  ConfNode();
  ConfNode(const YAML::Node& node);
  static const ConfNode LoadFile(std::string path);
  const ConfNode operator[](const std::string&) const;
};

}  // namespace base
}  // namespace common
