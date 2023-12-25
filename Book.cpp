#include "MyNamespace.h"
#include "Book.h"
#include "Date.h"
#include "Member.h"
#include <iostream>
#include <string>
#include <algorithm>

namespace MyNamespace {
  Book::Book(int bID, std::string bName, std::string authFirstN,std::string authLastN) : bookID(bID),bookName(bName),authorFirstName(authFirstN),authorLastName(authLastN),dueDateNotSet(true),dueDate(nullptr),borrower(nullptr) {
  }
  Book::~Book() {
    delete borrower;
    delete dueDate;
  }
  std::string Book::getBookID() const {
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
    Date newDueDate= currentDate.addDays(3);
    dueDate = new Date(newDueDate);
    dueDateNotSet = false;
  }
  void Book::returnBook() {
    if (borrower != nullptr) {
    std::vector<Book*>& bookVec = borrower->getBooksBorrowed();
    auto it = std::find(bookVec.begin(),bookVec.end(),this);
    if (it != bookVec.end()) {
     bookVec.erase(it);
    }
      delete dueDate;
      dueDate = nullptr;
      dueDateNotSet = true;
      delete borrower;
      borrower = nullptr;
    } else {
      throw std::logic_error("Book was not borrowed, can not be returned");
    }
  }
  
  void Book::borrowBook(Member &bur,Date due) {
    if (borrower == nullptr) {
    borrower = &bur;
    borrower->setBooksBorrowed(this);
    dueDate = new Date(due);
    std::cout <<"Book with ID " <<  this->getBookID() << " was successfully borrowed to member with ID " << borrower->getMemberID() << std::endl;
    } else {
      throw std::logic_error("Book already Borrowed");
    }
   }
  }



