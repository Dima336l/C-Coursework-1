#ifndef PERSON_H
#define PERSON_H
#include <string>
#include "MyNamespace.h"

namespace MyNamespace {
class Person {
 private:
  std::string name;
  std::string address;
  std::string email;
 public:
  std::string getName();
  void setName(std::string n);
  std::string getAddress();
  void setAddress(std::string ad);
  std::string getEmail();
  void setEmail(std::string);
};
}

#endif
