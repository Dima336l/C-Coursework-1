#ifndef BOOK_h
#define BOOK_h

#include <string>
#include "Member.h"

class Book { 
  private:
  int bookID;
  std::string bookName;
  std::string authorFirstName;
  std::string authorLastName;
  std::string bookType;
  Date dueDate;
  Member burrower;
  public:
  Book(int bookId, std::string bookN, std::string authFirstN, std::string authLastN);
  std::string getBookID();
  std::string getBookName();
  std::string getAuthorFirstName();
  std::string getAuthorLastName();
  Date getDueDate();
  void setDueDate(Date dueDate);
  void returnBook();
  void burrowBook(Member burrower, Date dueDate);
};

#endif
