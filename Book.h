#ifndef BOOK_H
#define BOOK_H
#include "Date.h"
#include "Member.h"
#include <string>

class Book {
 private:
  int bookID;
  std::string bookName;
  std::string authorFirstName;
  std::string authorLastName;
  std::string bookType;
  MyNamespace::Date dueDate;
  
  
}
