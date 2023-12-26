#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "MyNamespace.h"
#include "Date.h"
#include "Person.h"
#include "Librarian.h"
#include "Book.h"
#include "Member.h"
#include <vector>
#include <functional>
#include <sstream>
#include <iosfwd>

using namespace MyNamespace;
template<typename Function>
void redirectFunction(Function func, const std::string& str);
class NullStream : public std::ostream {
public:
  NullStream() : std::ostream(nullptr) {}
};
void redirectCoutToNullStream(bool suppress);
std::string captureOutput (std::function<void()> func);

TEST_CASE("Person class tests", "[PERSON]") {
  redirectCoutToNullStream(true);
  Person p;
  SECTION("Test default constructor") {
    REQUIRE(p.getName() == "");
    REQUIRE(p.getAddress() == "");
    REQUIRE(p.getEmail() == "");
  }
  SECTION ("Test setters and getters") {
    p.setName("Dumitru");
    p.setAddress("Colindale");
    p.setEmail("Nircadmitrii@icloud.com");
    REQUIRE(p.getName() == "Dumitru");
    REQUIRE(p.getAddress() == "Colindale");
    REQUIRE(p.getEmail() == "Nircadmitrii@icloud.com");
  }
  }

TEST_CASE("Librarian class tests", "[Librarian]") {
  std::string capturedOutput;
  Librarian* lib = new Librarian(1,"Dumitru","Colindale","Nircadmitrii@icloud.com",30000);
  SECTION("Test parameterized constructor and getters") {
    REQUIRE(lib->getName() == "Dumitru");
    REQUIRE(lib->getAddress() == "Colindale");
    REQUIRE(lib->getEmail() == "Nircadmitrii@icloud.com");
    REQUIRE(lib->getStaffID() == 1);
    REQUIRE(lib->getSalary() == 30000);
  }
  SECTION("Testing addMember function") {
    REQUIRE(Librarian::members.size() == 0);
    redirectFunction([&](const std::string& str) {lib->addMember(); }, "Dumitru\nColindale\nNircadmitrii@icloud.com\n");
    REQUIRE(Librarian::members.size() == 1);
    }
  SECTION("Testing calcFine function") {
    Book* newBook = new Book(100,"Rabbit","Joji","Ayr");
    Member* newMember = new Member(100,"Robert","Edgware","Edgware@icloud.com");
    Librarian::members.push_back(newMember);
    Librarian::books.push_back(newBook);
    redirectFunction([&](const std::string& str) {Date::setInitialDate(); }, "1\n12\n2000\n");
    Date* initialDate = Date::getCurrentDate();
    REQUIRE(initialDate->getDay() == 1);
    REQUIRE(initialDate->getMonth() == 12);
    REQUIRE(initialDate->getYear() == 2000);
    lib->issueBook(100,100);
    redirectFunction([&](const std::string& str) {Date::setInitialDate(); }, "5\n12\n2000\n"); // Simulating passage of time
    Date* futureDate = Date::getCurrentDate();
    REQUIRE(futureDate->getDay() == 5);
    REQUIRE(futureDate->getMonth() == 12);
    REQUIRE(futureDate->getYear() == 2000);
    capturedOutput = captureOutput([&] { lib->calcFine(100);});
    REQUIRE(capturedOutput == "\"Rabbit\" by Joji Ayr is 1 day past its due date.The amount you owe to the library is 1£.");
    lib->returnBook(100,100);
    capturedOutput = captureOutput([&] { lib->calcFine(100);});
    REQUIRE(capturedOutput == "This member has no books borrowed."); 
    Librarian::members.erase(Librarian::members.begin());
    Librarian::books.erase(Librarian::books.begin());
  }
}
/*
  SECTION("Testing issueBook function") {
    Book* book = new Book(1,"Sun","Andrei","Moraru");
    Book* book2 = new Book(2,"Moon","Octavian","Nirca");
    Member* member = new Member(2,"Dumitru","Colindale","Nircadmitrii@icloud.com");
    Librarian::members.push_back(member);
    Librarian::books.push_back(book);
    Librarian::books.push_back(book2);
    lib->issueBook(2,1);
    REQUIRE(member->getBooksBorrowed().size() == 1);
    REQUIRE_THROWS_AS((lib->issueBook(2,1)),std::runtime_error); // Issuing book that is already borrowed
    REQUIRE_THROWS_AS((lib->issueBook(3,2)),std::runtime_error); // Issuing a book that doesn't exist
    REQUIRE_THROWS_AS((lib->issueBook(4,1)),std::runtime_error); // Issuing a book to a non existing member		      
    }
  SECTION("Testing returnBook function") {
    REQUIRE(Librarian::members[1]->getBooksBorrowed().size() == 1);
    lib->returnBook(2,1);
    REQUIRE_THROWS_AS((lib->returnBook(2,1)),std::runtime_error); // Returning a book that has been returned
    REQUIRE_THROWS_AS((lib->returnBook(3,1)),std::runtime_error); // Returning a book by a member that is not registered
    REQUIRE_THROWS_AS((lib->returnBook(2,2)),std::runtime_error); // Returning a book that was not borrowed by the member
    REQUIRE(Librarian::members[1]->getBooksBorrowed().size() == 0);
    lib->issueBook(2,1);
    REQUIRE(Librarian::members[1]->getBooksBorrowed().size() == 1);
  }
  SECTION("Testing displayBorrowedBooks function") {
    std::string capturedOutput = captureOutput([&] { lib->displayBorrowedBooks(2);});
    REQUIRE(capturedOutput == "[\"Sun\" by Andrei Moraru]");
  }
}
/*
TEST_CASE("Date class tests","[Date]") {
  SECTION("Testing invalid date values") {
    REQUIRE_THROWS_AS(Date (32,1,2000), std::invalid_argument);
    REQUIRE_THROWS_AS(Date (1,13,2000), std::invalid_argument);
    REQUIRE_THROWS_AS(Date (1,12,-10), std::invalid_argument);
  }
  SECTION("Testing valid date values") {
    REQUIRE_NOTHROW(Date (1,12,2000));
    REQUIRE_NOTHROW(Date (5,3,1997));
    REQUIRE_NOTHROW(Date (10,1,1000));
  }
  SECTION("Testing modification of date components") {
    Date date(1,12,2000);
    REQUIRE(date.getDay() == 1);
    REQUIRE(date.getMonth()== 12);
    REQUIRE(date.getYear() == 2000);
    date.setDay(20);
    date.setMonth(3);
    date.setYear(2023);
    REQUIRE(date.getDay() == 20);
    REQUIRE(date.getMonth() == 3);
    REQUIRE(date.getYear() == 2023);
}
  SECTION("Testing Date copy constructor") {
    Date date1(1,12,3000);
    REQUIRE(date1.getDay() == 1);
    REQUIRE(date1.getMonth()== 12);
    REQUIRE(date1.getYear() == 3000);
    Date date2(date1);
    REQUIRE(date2.getDay() == 1);
    REQUIRE(date2.getMonth()== 12);
    REQUIRE(date2.getYear() == 3000);
  }
  SECTION("Testing leap year") {
    REQUIRE_NOTHROW(Date (29,2,2024));
    REQUIRE_THROWS_AS(Date (29,2,2022),std::invalid_argument);
  }
  SECTION("Testing add days function no changing month and year") {
    Date date(01,12,2000);
    Date newDate = date.addDays(3);
    REQUIRE(newDate.getDay() == 4);
    REQUIRE(newDate.getMonth() == 12);
    REQUIRE(newDate.getYear() == 2000);
  }
  SECTION("Testing add days function with month changing") {
    Date date (30,1,2000);
    Date newDate = date.addDays(3);
    REQUIRE(newDate.getDay() == 2);
    REQUIRE(newDate.getMonth() == 2);
    REQUIRE(newDate.getYear() == 2000);
  }
  SECTION("Testing add days function with month and year changing") {
    Date date (31,12,2000);
    Date newDate = date.addDays(3);
    REQUIRE(newDate.getDay() == 3);
    REQUIRE(newDate.getMonth() == 1);
    REQUIRE(newDate.getYear() == 2001);
  }
  SECTION("Testing add days function leap year") {
    Date date (25,2,2024);
    Date newDate = date.addDays(4);
    REQUIRE(newDate.getDay() == 29);
    REQUIRE(newDate.getMonth() == 2);
    REQUIRE(newDate.getYear() == 2024);
  }
  SECTION("Testing add days function with large values") {
    Date date (1,12,2000);
    Date newDate = date.addDays(69);
    REQUIRE(newDate.getDay() == 8);
    REQUIRE(newDate.getMonth() == 2);
    REQUIRE(newDate.getYear() == 2001);
  }
  SECTION("Testing add days function with even larger values") {
    Date date (1,12,2000);
    Date newDate = date.addDays(500);
    REQUIRE(newDate.getDay() == 15);
    REQUIRE(newDate.getMonth() == 4);
    REQUIRE(newDate.getYear() == 2002);
  }
  SECTION("Testing initial date setter") {
  std::stringstream outputCapture;
  std::streambuf* originalCout = std::cout.rdbuf();
  std::cout.rdbuf(outputCapture.rdbuf());
  std::stringstream input;
  input << "1\n2\n2023\n";
  std::streambuf* origCin = std::cin.rdbuf(input.rdbuf());
  Date::setInitialDate();
  std::cout.rdbuf(originalCout);
  std::cin.rdbuf(origCin);
  Date currentDate = Date::getCurrentDate();
  REQUIRE(currentDate.getDay() == 1);
  REQUIRE(currentDate.getMonth() == 2);
  REQUIRE(currentDate.getYear() == 2023);
  }
  SECTION("Test daysPassed function") {
  Date newDate (29,1,2023);
  int daysPassed = newDate.getDaysPassed();
  REQUIRE(daysPassed == 3);
  Date newBookDueDate(19,8,2023);
  daysPassed = newBookDueDate.getDaysPassed();
  REQUIRE(daysPassed == 199);
}
}
  TEST_CASE("Book class test","[Book]") {
    Date currentDate = Date::getCurrentDate();
    Member member (1,"Dumitru","Colindale","Nircadmitrii@icloud.com");
    Book book (1,"Sun","Dumitru","Nirca");
    SECTION("Testing Book Parameterized constructor and Getters") {
      REQUIRE(book.getBookID() == "1");
      REQUIRE(book.getAuthorFirstName() == "Dumitru");
      REQUIRE(book.getAuthorLastName() == "Nirca");
  }
    SECTION("Testing getDueDate function when due date not set") {
      REQUIRE_THROWS_AS(book.getDueDate(),std::logic_error);
    }
    SECTION("Testing setDueDate and getDueDate functions") {
      REQUIRE(currentDate.getDay() == 1);
      REQUIRE(currentDate.getMonth() == 2);
      REQUIRE(currentDate.getYear() == 2023);
      book.setDueDate(currentDate);
      Date bookDueDate = book.getDueDate();
      REQUIRE(bookDueDate.getDay() == 4);
      REQUIRE(bookDueDate.getMonth() == 2);
      REQUIRE(bookDueDate.getYear() == 2023);
    }
  }
 TEST_CASE("Member class test","[Member]") {
   Member* memberNew1 = new Member (1,"Dumitru","Colindale","Nircadmitrii@icloud.com");
   Member* memberNew2 = new Member (1,"Andrei","Nirca","AndreiNirca@icloud.com");
   Book* bookNew  = new Book(1,"Moon","Dumitru","Nirca");
   size_t initialSize;
   size_t finalSize;
   SECTION("Testing member constructor, burrowBook and returnBook functions") {
      REQUIRE(memberNew1->getMemberID() == "1");
      REQUIRE(memberNew1->getName() == "Dumitru");
      REQUIRE(memberNew1->getAddress() == "Colindale");
      REQUIRE(memberNew1->getEmail() == "Nircadmitrii@icloud.com");
      Date currentDate = Date::getCurrentDate();
      bookNew->setDueDate(currentDate);
      Date bookNewDueDate = bookNew->getDueDate();
      REQUIRE(memberNew1->getBooksBorrowed().size() == 0);
      REQUIRE_THROWS_AS((bookNew->returnBook()),std::logic_error);
      bookNew->borrowBook(*memberNew1,bookNewDueDate);
      REQUIRE_THROWS_AS((bookNew->borrowBook(*memberNew2,bookNewDueDate)),std::logic_error);
      REQUIRE(memberNew1->getBooksBorrowed().size() == 1);
      bookNew->returnBook();
      REQUIRE(memberNew1->getBooksBorrowed().size() == 0);
      bookNew->borrowBook(*memberNew2,bookNewDueDate);
      REQUIRE(memberNew2->getBooksBorrowed().size() == 1);
      }
 }
 */
template<typename Function>
void redirectFunction(Function func, const std::string& str) {
    // Redirect std::cin to input
    std::stringstream input(str);
    std::streambuf* origCin = std::cin.rdbuf(input.rdbuf());
    // Call the provided function
    func(str);
    // Restore original std::cin
    std::cin.rdbuf(origCin);
}

void redirectCoutToNullStream(bool suppress) {
  static NullStream nullStream;
  static std::streambuf* originalCoutBuffer = nullptr;
  if (!originalCoutBuffer) {
    originalCoutBuffer = std::cout.rdbuf();
  }
  if (suppress) {
  std::cout.rdbuf(nullStream.rdbuf());
  } else {
    std::cout.rdbuf(originalCoutBuffer);
  }
}

std::string captureOutput (std::function<void()> func) {
  std::stringstream outputCapture;
  std::streambuf* originalCoutBuffer = std::cout.rdbuf(); // Save original cout buffer
  std::cout.rdbuf(outputCapture.rdbuf());
  func();
  std::cout.rdbuf(originalCoutBuffer);
  std::string capturedOutput = outputCapture.str();
  capturedOutput.erase(std::remove(capturedOutput.begin(), capturedOutput.end(), '\n'), capturedOutput.end());
  return capturedOutput;
}

