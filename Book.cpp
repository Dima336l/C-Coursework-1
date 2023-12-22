#include "MyNamespace.h"
#include "Book.h"
#include "Date.h"
#include "Member.h"
#include <iostream>
#include <string>
#include <memory>

namespace MyNamespace {
  Book::Book(int bID, std::string bName, std::string authFirstN,std::string authLastN) : dueDateNotSet(true), dueDate(nullptr), burrower(nullptr) {
    bookID = bID;
    bookName = bName;
    authorFirstName = authFirstN;
    authorLastName = authLastN;
      }
  std::string Book::getBookID() {
    return std::to_string(bookID);
  }
  std::string Book::getBookName() {
    return bookName;
  }
  std::string Book::getAuthorFirstName() {
    return authorFirstName;
  }
  std::string Book::getAuthorLastName() {
    return authorLastName;
  }
  Date Book::getDueDate() {
    if (dueDateNotSet) {
      throw std::logic_error("Due date not set. Set it first");
    }
      return *dueDate;
  }
  void Book::setDueDate(Date currentDate) {
    dueDate= std::make_unique<Date>(currentDate.addDays(3));
    dueDateNotSet = false;
  }
  void Book::returnBook() {
    dueDate.reset();
    dueDateNotSet = true;
  }
  
  void Book::borrowBook(Member& bur,Date due) {
    if (burrower == nullptr) {
      burrower = &bur;
      dueDate = std::make_unique<Date>(due);
      bur.setBooksBorrowed(this);
    }
    }
}
