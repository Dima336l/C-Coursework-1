#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include "Person.h"
#include "MyNamespace.h"
#include <string>

namespace MyNamespace {
  class Librarian : public Person {
 private :
  int staffId;
  int salary;
 public:
  static std::vector<Member*> members;
  Librarian();
  Librarian(int staffId, std::string name, std::string address, std::string email, int salary);
  Librarian();
  void addMember();
  void issueBook(int memberID, int bookID);
  void returnBook(int memberID, int bookID);
  void displayBurrowedBooks(int memberID);
  void calcFine(int memberID);
  int getStaffID();
  void setStaffID(int staffID);
  int getSalary();
  void setSalary(int salary);
};
}
#endif
