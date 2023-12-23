#include "MyNamespace.h"
#include "Book.h"
#include "Date.h"
#include "Member.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <memory>

namespace MyNamespace {
  Book::Book(int bID, std::string bName, std::string authFirstN,std::string authLastN) : dueDateNotSet(true), dueDate(nullptr), borrower(nullptr) {
    bookID = bID;
    bookName = bName;
    authorFirstName = authFirstN;
    authorLastName = authLastN;
      }
  Book::Book(const Book& other) 
    : bookID(other.bookID),
      bookName(other.bookName),
      authorFirstName(other.authorFirstName),
      authorLastName(other.authorLastName),
      dueDateNotSet(other.dueDateNotSet),
      dueDate(nullptr)
  {
      if (other.dueDate) {
	dueDate = new Date(*other.dueDate);
      }
      if (other.borrower) {
      borrower = new Member(*other.borrower);
    }
  }
  Book::~Book() {
    delete borrower;
    delete dueDate;
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
    Date newDueDate= currentDate.addDays(3);
    dueDate = new Date(newDueDate);
    dueDateNotSet = false;
  }
  void Book::returnBook() {
    std::vector<Book*>& bookVec = borrower->getBooksBorrowed();
    auto it = std::find(bookVec.begin(),bookVec.end(),this);
    if (it != bookVec.end()) {
     bookVec.erase(it);
    std::cout<<"Book deleted" << std::endl;
    if (dueDate) {
      delete dueDate;
      dueDate = nullptr;
      dueDateNotSet = true;
    }
  }
  }
  
  void Book::borrowBook(Member &bur,Date due) {
    borrower = &bur;
    std::cout << borrower->getName() << std::endl;
    dueDate = new Date(due);
      }
  }



