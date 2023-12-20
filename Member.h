#ifndef MEMBER_H
#define MEMBER_H

#include "Person.h"
#include "Book.h"
#include <vector>

class Member : public Person {
 private:
  int memberId;
  std::vector <Book> booksLoaned;
public:
  Member(int memberID, std::string name, std::string address, std::string email);
  std::string getMemberID();
  std::vector <Book> getBooksBurrowed();
  void setBooksBurrowed(Book book);
};

#endif
  
