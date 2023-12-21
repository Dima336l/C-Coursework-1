#include "Person.h"

namespace MyNamespace {
  std::string MyNamespace::Person::getName() {
  return name;
}

  void MyNamespace::Person::setName(std::string n) {
  name = n;
}

  std::string MyNamespace::Person::getAddress() {
  return address;
}

  void MyNamespace::Person::setAddress(std::string ad) {
  address = ad;
}

  std::string MyNamespace::Person::getEmail() {
  return email;
}

  void MyNamespace::Person::setEmail(std::string e) {
  email = e;
}
}
