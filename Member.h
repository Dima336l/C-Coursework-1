#ifndef MEMBER_H
#define MEMBER_H

#include "MyNamespace.h"
#include "Person.h"
#include "Book.h"
#include <vector>

namespace MyNamespace {
  class Book;
class Member : public Person {
 private:
  int memberId;
  std::vector <Book*> booksLoaned;
public:
  Member(int memberID, std::string name, std::string address, std::string email);
  std::string getMemberID();
  std::vector <Book*>& getBooksBorrowed();
  void setBooksBorrowed(Book* book);
};
}
#endif
  
