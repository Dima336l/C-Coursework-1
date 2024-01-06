#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include "MyNamespace.h"
#include "Person.h"
#include "Member.h"
#include "Date.h"
#include "Book.h"
#include "Global.h"
#include <string>
#include <vector>
#include <iostream>
#include <regex>
#include <limits>
#include <algorithm>

namespace MyNamespace {
  class Librarian : public Person {
 private :
  int staffId;
  int salary;
    bool containsOnlyAlphabet(const std::string& str);
    bool isValidEmail(const std::string & email);
    std::vector<Member*>::iterator findMemberByID(int memberID);
    std::vector<Book*>::iterator findBookByID(int bookID);
    int calcFineForOneBook(Book* book,std::vector<Member*>::iterator memberit, int finePerDay);
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
    void handleBookIssue(std::vector<Member*>::iterator& memberit,std::vector<Book*>::iterator& bookit);
    void handleBookReturn(std::vector<Book*>::iterator& bookit, int memberID);
    void calcFine(int memberID);
    void printFine(int fine);
    int getStaffID();
    void setStaffID(int staffID);
    void displayMemberInfo(int memberID, std::string memberName, std::string memberAddress, std::string memberEmail);
    int getSalary();
    void setSalary(int salary);
};
}
#endif
