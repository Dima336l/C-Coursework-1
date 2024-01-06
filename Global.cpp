#include "Global.h"

namespace MyNamespace {
  std::vector<Member*> members;
  std::vector<Book*> books;
  bool fineSet = false;
  bool numOfDaysSet = false;
  int finePerDay = 1;
  int numOfDays = 1;
  std::unordered_map<Member*, bool> objectMap;
}
