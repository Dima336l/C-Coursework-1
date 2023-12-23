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
  std::string getName() const;
  void setName(std::string n);
  std::string getAddress() const;
  void setAddress(std::string ad);
  std::string getEmail() const;
  void setEmail(std::string);
};
}

#endif
