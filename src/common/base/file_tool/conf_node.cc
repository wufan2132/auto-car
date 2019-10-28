

#include "conf_node.h"
#include <glog/logging.h>

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
    const ConfNode& node = this->YAML::Node::operator[](str);
    if (!node.IsNull()) {
      return node;
    }
  } catch (std::exception e) {
    CHECK(NULL) << "yaml load file failed, can not find at: " << str;
    return ConfNode();
  }
  CHECK(NULL) << "yaml load file failed, can not find at: " << str;
  return ConfNode();
}

bool ConfNode::IsDefined(const std::string& str) const {
  return this->YAML::Node::operator[](str).IsDefined();
}

// const ConfNode::T ConfNode::as() const {
//   try {
//     return this->YAML::Node::operator[](str);
//   } catch (std::exception e) {
//     CHECK(NULL) << "yaml load file failed, can not find at: " << str;
//     return ConfNode();
//   }
// }

}  // namespace base
}  // namespace common