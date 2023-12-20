#include "Member.h"
#include <string>


Member::Member(int memberID,std::string n,std::string ad,std::string em) {
  setName(n);
  setAddress(ad);
  setEmail(e);
  memberId = memberID;
}

std::string getMemberID() {
  return std::to_string(memberId);
}

std::vector <Book> getBooksBurrowed() {
  return booksLoaned;
}

void setBooksBurrowed(book: Book) {
  booksLoaned.push_back(Book);
}
