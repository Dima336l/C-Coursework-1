#ifndef MYNAMESPACE_BOOK_H
#define MYNAMESPACE_BOOK_H

#include "MyNamespace.h"
#include "Date.h"
#include "Member.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <limits>

namespace MyNamespace {
  class Date;
  class Member;
class Book { 
  private:
  bool dueDateNotSet;
  int bookID;
  std::string bookName;
  std::string authorFirstName;
  std::string authorLastName;
  std::string bookType;
  Date* dueDate;
  Member* borrower;
  public:
  ~Book();
  Book(int bookId, std::string bookN, std::string authFirstN, std::string authLastN);
  std::string getBookID() const;
  std::string getBookName();
  std::string getAuthorFirstName();
  std::string getAuthorLastName();
  void resetDaysSetFlag();
  int determineNumOfDays();
  int chooseAnotherDate();
  Date getDueDate();
  bool checkIfDateSet();
  void setDueDate(Date* dueDate);
  void returnBook();
  void borrowBook(Member &burrower, Date dueDate);
};
}

#endif
