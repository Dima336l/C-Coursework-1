#include "Person.h"

namespace MyNamespace {
  std::string Person::getName() {
  return name;
}

  void Person::setName(std::string n) {
  name = n;
}

  std::string Person::getAddress() {
  return address;
}

  void Person::setAddress(std::string ad) {
  address = ad;
}

  std::string Person::getEmail() {
  return email;
}

  void Person::setEmail(std::string e) {
  email = e;
}
}
