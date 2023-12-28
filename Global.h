#ifndef GLOBAL_H
#define GLOBAL_H

#include "MyNamespace.h"
#include "Person.h"
#include "Member.h"
#include "Book.h"
#include <vector>

namespace MyNamespace {
extern std::vector<Member*> members;
extern std::vector<Book*> books;
extern bool fineSet;
extern bool numOfDaysSet;
extern int numOfDays;
extern int finePerDay;
}

#endif
