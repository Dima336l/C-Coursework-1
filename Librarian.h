#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include "Person.h"
#include <string>

class Librarian : public Person {
 private :
  int staffId;
  int salary;
 public:
  Librarian();
  Librarian(int staffId, std::string name, std::string address, std::string email, int salary);
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

#endif