#include "Librarian.h"
#include <string>

namespace MyNamespace {
  Librarian::Librarian(int staffID, std::string name, std::string address, std::string email, int sal) {
  //Seting values using setters from base class
  setName(name);
  setAddress(address);
  setEmail(email);
  
  //Setting Libriarian-specific members
  Librarian::setStaffID(staffID);
  Librarian::setSalary(sal);
}

  Librarian::Librarian() {
  staffId = 0;
  salary = 0;
}

  void Librarian::setStaffID(int id) {
  staffId = id;
}

  void Librarian::setSalary(int sal) {
  salary = sal;
}

  int Librarian::getStaffID() {
  return staffId;
}

  int Librarian::getSalary() {
  return salary;
}

void Librarian::addMember() {
  int memberId;
  std::cout << "Enter member ID: ";
  std::cin >> memberId;
  std::cout << std::endl;
  std::string name;
  std::cout << "Enter member name: ";
  std::cin >> name;
  std::cout << std::endl;
  std::string address;
  std::cout << "Enter member address: ";
  std::cin >> address;
  std::string email;
  std::cout << "Enter email: ";
  std::cin >> email;
  Member* member = new Member(memberId,name,address,email);
  members.push_back(member);
}
