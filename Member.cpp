#include "Member.h"
#include "Book.h"
#include <string>
#include <vector>
#include <iostream>

namespace MyNamespace {
  Member::Member(int memberID,std::string n,std::string ad,std::string em) {
    memberId = memberID;
    setName(n);
    setAddress(ad);
    setEmail(em);
    booksLoaned = std::vector<Book*>();
     }
    
  Member::Member(const Member& other) {
    setName(other.getName());
    setAddress(other.getAddress());
    setEmail(other.getEmail());
    memberId = std::stoi(other.getMemberID());
    for (const auto& book : other.booksLoaned) {
      Book * copiedBook = new Book(*book);
      booksLoaned.push_back(copiedBook);
    }
    }
  

  Member::~Member() {
    for (auto& book : booksLoaned) {
      delete book;
    }
    booksLoaned.clear();
  }
  
  std::string Member::getMemberID()const {
  return std::to_string(memberId);
}
  
 const  std::vector <Book*>& Member::getBooksBorrowed() const {
    return booksLoaned;
  }
  std::vector <Book*>& Member::getBooksBorrowed() {
    return booksLoaned;
  }

  void Member::setBooksBorrowed(Book* book) {
     booksLoaned.push_back(book);
    }
}

