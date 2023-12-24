#include "Person.h"

namespace MyNamespace {
  std::string Person::getName() const {
  return name;
}

  void Person::setName(std::string n) {
  name = n;
}

  std::string Person::getAddress() const {
  return address;
}

  void Person::setAddress(std::string ad) {
  address = ad;
}

  std::string Person::getEmail() const {
  return email;
}

  void Person::setEmail(std::string e) {
  email = e;
}
}
