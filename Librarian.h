#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include "MyNamespace.h"
#include "Person.h"
#include "Member.h"
#include "Book.h"
#include "Global.h"
#include <string>
#include <vector>

namespace MyNamespace {
  class Librarian : public Person {
 private :
  int staffId;
  int salary;
    bool containsOnlyAlphabet(const std::string& str);
    bool isValidEmail(const std::string & email);
    std::vector<Member*>::iterator findMemberByID(int memberID);
    std::vector<Book*>::iterator findBookByID(int bookID);
    void calcFineForOneBook(Book* book, int finePerDay);
    std::string getMemberName();
    std::string getMemberAddress();
    std::string getMemberEmail();
    bool handleMemberIt(std::vector<Member*>::iterator,int memberID);
    bool handleBookIt(std::vector<Book*>::iterator,int bookID);
    int determineFine();
 public:
    Librarian(int staffId, std::string name, std::string address, std::string email, int salary);
    void resetFineSetFlag();
    void addMember();
    void issueBook(int memberID, int bookID);
    void returnBook(int memberID, int bookID);
    void displayBorrowedBooks(int memberID);
    void handleBookIssue(std::vector<Member*>::iterator& memberit,std::vector<Book*>::iterator& bookit,int memberID,int bookID);
    void handleBookReturn(std::vector<Member*>::iterator& memberit, std::vector<Book*>::iterator& bookit, int memberID, int bookID);
    void calcFine(int memberID);
    int getStaffID();
    void setStaffID(int staffID);
    int getSalary();
    void setSalary(int salary);
};
}
#endif
