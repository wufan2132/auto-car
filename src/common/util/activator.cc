#include "activator.h"

#include "common/base/log.h"

namespace common {
namespace util {

Activator::Activator(int lock_num) : lock_num_(lock_num), unlock_num_(-1){};

Activator::~Activator() = default;

void Activator::Activate(std::string str) {
  if (!activate_set.count(str)) {
    activate_set.insert(str);
    AINFO << "Activator: activate " << str;
  }
}
void Activator::Deactivate(std::string str) {
  if (activate_set.count(str)) {
    activate_set.erase(str);
    AINFO << "Activator: deactivate " << str;
  }
}
bool Activator::State() {
  if (activate_set.size() >= lock_num_) {
    return 1;
  }
  if (activate_set.size() != unlock_num_) {
    unlock_num_ = activate_set.size();
    AINFO << "Activator: waitting...";
    AINFO << "it remain " << lock_num_ - unlock_num_ << "lock";
    return 0;
  }
  return 0;
}

}  // namespace util
}  // namespace common