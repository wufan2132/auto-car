

#include <glog/logging.h>
#include "conf_node.h"

namespace common {
namespace base {

ConfNode::ConfNode() : YAML::Node() {}

ConfNode::ConfNode(const YAML::Node& node) : YAML::Node(node) {}

const ConfNode ConfNode::LoadFile(std::string path) {
  try {
    return ConfNode(YAML::LoadFile(path));
  } catch (std::exception e) {
    CHECK(NULL) << "yaml load file failed, can not find file at: " << path;
    return ConfNode(YAML::Node());
  }
}

const ConfNode ConfNode::operator[](const std::string& str) const {
  try {
    return this->ConfNode::operator[](str);
  } catch (std::exception e) {
    CHECK(NULL) << "yaml load file failed, can not find at: " << str;
    return ConfNode();
  }
}

}  // namespace base
}  // namespace common