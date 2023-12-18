#include "Librarian.h"
#include <string>

Librarian::Librarian() {
}
Librarian::Librarian(int staffID, std::string name, std::string address, std::string email, int sal) {
  //Seting values using setters from base class
  setName(name);
  setAddress(address);
  setEmail(email);
  
  //Setting Libriarian-specific members
  Librarian::setStaffID(staffID);
  Librarian::setSalary(sal);
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

