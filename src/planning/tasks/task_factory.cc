#include "task_factory.h"

namespace planning {

std::unique_ptr<Task> TaskFactory::CreatObject(std::string type,
                                               const common::base::ConfNode& conf) {
  auto id_iter = producers_.find(type);
  if (id_iter != producers_.end()) {
    return std::unique_ptr<Task>((id_iter->second)(conf));
  }
  return nullptr;
}

}  // namespace planning