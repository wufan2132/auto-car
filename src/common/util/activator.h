
#pragma once

#include <unordered_set>

namespace common {
namespace util {

    
class Activator {
 public:
  Activator(int lock_num = 1);
  ~Activator();

  void Activate(std::string str = "default");
  void Deactivate(std::string str = "default");
  bool State();

 private:
  std::unordered_set<std::string> activate_set;
  int lock_num_;
  int unlock_num_;
};

}  // namespace util
}  // namespace common