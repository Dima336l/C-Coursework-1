#include "Librarian.h"
#include "Member.h"
#include "Date.h"
#include <string>
#include <vector>
#include <iostream>
#include <regex>
#include <limits>
#include <algorithm>

namespace MyNamespace {
  std::vector<Member*> Librarian::members;
  std::vector<Book*> Librarian::books;
  Librarian::Librarian(int staffID, std::string name, std::string address, std::string email, int sal) {
    //Seting values using setters from base class
    setName(name);
    setAddress(address);
    setEmail(email);
  
    //Setting Libriarian-specific members
    Librarian::setStaffID(staffID);
    Librarian::setSalary(sal);
  }

  Librarian::Librarian() {
    staffId = 0;
    salary = 0;
  }

  void Librarian::setStaffID(int id) {
    staffId = id;
  }

  void Librarian::setSalary(int sal) {
    salary = sal;
  }

  int Librarian::getStaffID() {
    return staffId;
  }

  int Librarian::getSalary() {
    return salary;
  }
  bool Librarian::isValidEmail(const std::string& email) {
    const std::regex emailRegex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return std::regex_match(email, emailRegex);
  }

  bool Librarian::containsOnlyAlphabet(const std::string& str) {
    return std::all_of(str.begin(),str.end(),::isalpha);
  }

  std::string Librarian::getMemberName() {
    std::string name;
    while (true) {
      std::cout << "Enter member name: ";
      std::getline(std::cin, name);
      if (containsOnlyAlphabet(name)) {
	if (name.empty()) {
	  std::cout << "Name cannot be empty." << std::endl;
	} else {
	  break;
	}
      } else {
	std::cout << "Invalid input. Member name should only contain leters." << std::endl;
      }
    }
    return name;
  }

  std::string Librarian::getMemberAddress() {
    std::string address;
    while (true) {
      std::cout << "Enter member adress: ";
      std::getline(std::cin, address);
      if (!address.empty()) {
	break;
      } else {
	std::cout << "Invalid input. Address cannot be empty." << std::endl;
      }
    }
    return address;
  }

  std::string Librarian::getMemberEmail() {
    std::string email;
    while (true) {
      std::cout << "Enter email: ";
      std::cin >> email;
      if (Librarian::isValidEmail(email)) {
	if (std::find_if(Librarian::members.begin(),Librarian::members.end(),[&email](Member* m) { return m->getEmail() == email; }) == Librarian::members.end())  {
	  break;
	}else {
	  std::cout << "A member with this email is already registered." << std::endl;
	} 
      } else {
	std::cout << "Invalid email format. Please enter valid email." << std::endl;
      }
    }
    return email;
  }
  void Librarian::addMember() {;
    std::string name,address,email;
    int memberId = Librarian::members.size() + 1;
    name = Librarian::getMemberName();
    address = Librarian::getMemberAddress();
    email = Librarian::getMemberEmail();
    Member* member = new Member(memberId,name,address,email);
    members.push_back(member);
  }


  std::vector<Member*>::iterator Librarian::findMemberByID(int memberID) {
    return std::find_if(Librarian::members.begin(), Librarian::members.end(),
			[memberID](const Member* m) {
			  return m->getMemberID() == std::to_string(memberID);
			});
  }

  std::vector<Book*>::iterator Librarian::findBookByID(int bookID) {
    return std::find_if(Librarian::books.begin(), Librarian::books.end(),
			[bookID](const Book* b) {
			  return b->getBookID() == std::to_string(bookID);
			});
  }

  void Librarian::handleBookIssue(std::vector<Member*>::iterator memberit, std::vector<Book*>::iterator bookit,int memberID, int bookID) {
    Date currentDate = Date::getCurrentDate();
    (*bookit)->setDueDate(currentDate);
    Date bookDueDate = (*bookit)->getDueDate();
    (*bookit)->borrowBook(**memberit,bookDueDate);
  }


  void Librarian::issueBook(int memberID, int bookID) {
    auto memberit = Librarian::findMemberByID(memberID);
    auto bookit = Librarian::findBookByID(bookID);
    if (!(memberit != Librarian::members.end())) {
      std::cout << "Member with ID " << memberID << " was not found" << std::endl;
      return;
    }
    if (!(bookit != Librarian::books.end())) {
      std::cout << "Book with ID " << bookID << " was not found" << std::endl;
      return;
    }
    Librarian::handleBookIssue(memberit,bookit,memberID,bookID);
  }

  void Librarian::handleBookReturn(std::vector<Member*>::iterator memberit, std::vector<Book*>::iterator bookit, int memberID, int bookID) {
    std::cout << "Book with ID " << bookID << " was successfully returned by member with ID " << memberID << std::endl;
    (*bookit)->returnBook();
  }
  
  void Librarian::returnBook(int memberID,int bookID) {
    auto memberit = Librarian::findMemberByID(memberID);
    auto bookit = Librarian::findBookByID(bookID);
    if (!(memberit != Librarian::members.end())) {
      std::cout << "Member with ID " << memberID << " was not found" << std::endl;
      return;
    }
    if (!(bookit != Librarian::books.end())) {
      std::cout << "Book with ID " << bookID << " was not found" << std::endl;
      return;
    }
    Librarian::handleBookReturn(memberit,bookit,memberID,bookID);
  }
  void Librarian::calFineForOneBook(Book* book) {
    Date bookDueDate = book->getDueDate();
    int daysPassed = bookDueDate.getDaysPassed();
    const int finePerDay = 1;
    int fineAmount = 0;
    if (daysPassed != 0) {
      std::cout << "The book with name " << book->getBookName() << " is " << daysPassed << " days past its due date." << std::endl;
      std::cout << "The amount you owe to the library is " << daysPassed*finePerDay << "£." << std::endl;
    }
    }
  
  void Librarian::calcFine(int memberID){
    auto memberit = Librarian::findMemberByID(memberID);
    if (!(memberit != Librarian::members.end())) {
      std::cout << "Member with ID " << memberID << " was not found" << std::endl;
      return;
    }
    const auto& borrowedBooks = memberit->getBooksBorrowed();
    for (const auto& book: borrowedBooks) {
      Librarian::calcFineForOneBook(book);
    }
    
  }
}
