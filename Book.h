#ifndef MYNAMESPACE_BOOK_H
#define MYNAMESPACE_BOOK_H

#include <string>
#include "MyNamespace.h"
#include <memory>

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
  std::unique_ptr<Date> dueDate;
  Member* burrower;
  public:
  Book(int bookId, std::string bookN, std::string authFirstN, std::string authLastN);
  std::string getBookID();
  std::string getBookName();
  std::string getAuthorFirstName();
  std::string getAuthorLastName();
  Date getDueDate();
  void setDueDate(Date dueDate);
  void returnBook();
  void borrowBook(Member& burrower, Date dueDate);
};
}

#endif
