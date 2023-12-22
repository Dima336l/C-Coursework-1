#include "Member.h"
#include <string>
#include <vector>

namespace MyNamespace {
  Member::Member(int memberID,std::string n,std::string ad,std::string em) : booksLoaned() {
    setName(n), setAddress(ad), setEmail(em), memberId = memberID;
}

  std::string Member::getMemberID() {
  return std::to_string(memberId);
}
  
  std::vector <Book*>& Member::getBooksBorrowed() {
    return booksLoaned;
  }

  void Member::setBooksBorrowed(Book* book) {
    booksLoaned.push_back(book);
  } 
}
