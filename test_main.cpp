#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "MyNamespace.h"
#include "Date.h"
#include "Person.h"
#include "Librarian.h"
#include "Book.h"
#include "Member.h"
#include "Global.h"
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
void extractOutput(std::string &str);

TEST_CASE("Person class tests", "[PERSON]") {
  redirectCoutToNullStream(true);
  Person p;
  SECTION("Test default constructor") {
    std::cout << finePerDay << std::endl;
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
  SECTION("Test parameterized constructor and getters and setters") {
    REQUIRE(lib->getName() == "Dumitru");
    REQUIRE(lib->getAddress() == "Colindale");
    REQUIRE(lib->getEmail() == "Nircadmitrii@icloud.com");
    REQUIRE(lib->getStaffID() == 1);
    REQUIRE(lib->getSalary() == 30000);
    lib->setStaffID(5);
    lib->setSalary(10000);
    REQUIRE(lib->getStaffID() == 5);
    REQUIRE(lib->getSalary() == 10000);
    
  }
  SECTION("Testing addMember function") {
    REQUIRE(members.size() == 0);
    redirectFunction([&](const std::string& str) {lib->addMember(); }, "Dumitru\nColindale\nNircadmitrii@icloud.com\n");
    REQUIRE(members.size() == 1);
  }
  SECTION("Testing calcFine function") {
    Book* newBook = new Book(100,"Rabbit","Joji","Ayr");
    Member* newMember = new Member(100,"Robert","Edgware","Edgware@icloud.com");
    members.push_back(newMember);
    books.push_back(newBook);
    redirectFunction([&](const std::string& str) {Date::setInitialDate(); }, "1\n12\n2000\n");
    redirectFunction([&](const std::string& str) {lib->issueBook(100,100);}, "N\n");
    capturedOutput = captureOutput ([&] {redirectFunction([&](const std::string& str) {lib->calcFine(100);}, "N\n");});
    extractOutput(capturedOutput);
    REQUIRE(capturedOutput == "\"Rabbit\" by Joji Ayr is due in 3 days. Nothing is owed to the library.");
    redirectFunction([&](const std::string& str) {Date::setInitialDate(); }, "6\n12\n2000\n");
    capturedOutput = captureOutput([&] { lib->calcFine(100);});
    REQUIRE(capturedOutput == "\"Rabbit\" by Joji Ayr is 2 days past its due date.The amount you owe to the library is 2£.");
  }
  SECTION("Testing issueBook function") {
    Book* book = new Book(1,"Sun","Andrei","Moraru");
    Book* book2 = new Book(2,"Moon","Octavian","Nirca");
    Member* member = new Member(2,"Dumitru","Colindale","Nircadmitrii@icloud.com");
    members.push_back(member);
    books.push_back(book);
    books.push_back(book2);
    lib->issueBook(2,1);
    REQUIRE(member->getBooksBorrowed().size() == 1);
    REQUIRE_THROWS_AS((lib->issueBook(2,1)),std::runtime_error); // Issuing book that is already borrowed
    std::stringstream errorStream;
    std::streambuf* oldCerrBuf = std::cerr.rdbuf(errorStream.rdbuf());
    lib->issueBook(3,2); // Issuing a book to a member that is not registered
    std::cerr.rdbuf(oldCerrBuf);
    std::string errorMessage = errorStream.str();
    REQUIRE(errorMessage.find("Member with ID 3 was not found.") != std::string::npos);		     
  }
  SECTION("Testing returnBook function") {
    Member* member = new Member(69,"Octavian","Chisinau","Octavian@icloud.com");
    Book* book = new Book(69,"C++","Ion","Gandon");
    Book* book2 = new Book(70,"C","Pavel","Gordon");
    members.push_back(member);
    books.push_back(book);
    books.push_back(book2);
    lib->issueBook(69,69);
    REQUIRE(member->getBooksBorrowed().size() == 1);
    lib->returnBook(69,69);
    REQUIRE(member->getBooksBorrowed().size() == 0);
    REQUIRE_THROWS_AS((lib->returnBook(69,69)),std::runtime_error); // Returning a book that has been returned
    std::stringstream errorStream;
    std::streambuf* oldCerrBuf = std::cerr.rdbuf(errorStream.rdbuf());
    lib->returnBook(70,69); // Returning a book my a member that is not registered
    std::cerr.rdbuf(oldCerrBuf);
    std::string errorMessage = errorStream.str();
    REQUIRE(errorMessage.find("Member with ID 70 was not found.") != std::string::npos);
    REQUIRE_THROWS_AS((lib->returnBook(69,70)), std::runtime_error); // Book not borrowed by existing member
  }
  SECTION("Testing displayBorrowedBooks function") {
    std::stringstream errorStream;
    std::streambuf* oldCerrBuf = std::cerr.rdbuf(errorStream.rdbuf());
    lib->displayBorrowedBooks(69); // No books borrowed
    std::cerr.rdbuf(oldCerrBuf);
    std::string errorMessage = errorStream.str();
    REQUIRE(errorMessage.find("Member with ID 69 has no books borrowed.") != std::string::npos);
    lib->issueBook(69,69);
    capturedOutput = captureOutput([&] { lib->displayBorrowedBooks(69);});
    REQUIRE(capturedOutput == "[\"C++\" by Ion Gandon]");
  }
}

TEST_CASE("Date class tests","[Date]") {
  SECTION("Testing valid date values") {
    REQUIRE_NOTHROW(Date (1,12,2000));
    REQUIRE_NOTHROW(Date (5,3,1997));
    REQUIRE_NOTHROW(Date (10,1,1000));
  }
  SECTION("Testing invalid date values") {
    REQUIRE_THROWS_AS((Date (-5,3,2000)),std::invalid_argument);
    REQUIRE_THROWS_AS((Date (32,13,3000)),std::invalid_argument);
  }
  SECTION("Testing date setters and getters") {
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
    redirectFunction([&](const std::string& str) {Date::setInitialDate(); }, "1\n2\n2023\n");
    Date* currentDate = Date::getCurrentDate();
    REQUIRE(currentDate->getDay() == 1);
    REQUIRE(currentDate->getMonth() == 2);
    REQUIRE(currentDate->getYear() == 2023);
  }
  SECTION("Testing compare dates function") {
    int compareDates;
    Date date1(1,2,2023);
    compareDates = date1.compareDates();
    REQUIRE(compareDates == 0);
    date1.setDay(5);
    compareDates = date1.compareDates();
    REQUIRE(compareDates == 1);
    date1.setMonth(1);
    compareDates = date1.compareDates();
    REQUIRE(compareDates == -1);
    
  }
  SECTION("Testing countDaysPassed and getDaysPassed functions") {
    Date date1 (30,1,2023);
    int daysRemaining = date1.countDaysPassed();
    int compareDates = date1.compareDates();
    int daysRemainingFromCountDaysPassed = date1.getDaysPassed(compareDates);
    REQUIRE(daysRemaining == 2);
    REQUIRE(daysRemainingFromCountDaysPassed == 2);
  }
  SECTION("Testing countDaysRemaining and getDaysPassed function") {
    Date date1 (5,2,2023);
    int daysRemaining = date1.countDaysRemaining();
    int compareDates = date1.compareDates();
    int daysRemainingFromCountDaysPassed = date1.getDaysPassed(compareDates);
    REQUIRE(daysRemaining == 4);
    REQUIRE(daysRemainingFromCountDaysPassed == 4);
  }
}
TEST_CASE("Book class test","[Book]") {
  Member* member = new Member (1,"Dumitru","Colindale","Nircadmitrii@icloud.com");
  Book* book = new Book (1,"Sun","Dumitru","Nirca");
  SECTION("Testing Book Parameterized constructor and Getters") {
    REQUIRE(book->getBookID() == "1");
    REQUIRE(book->getAuthorFirstName() == "Dumitru");
    REQUIRE(book->getAuthorLastName() == "Nirca");
  }
  SECTION("Testing getDueDate function when due date not set") {
    REQUIRE_THROWS_AS(book->getDueDate(),std::logic_error);
  }
  SECTION("Testing setDueDate and getDueDate functions") {
    Date* currentDate = Date::getCurrentDate();
    book->setDueDate(currentDate);
    Date bookDueDate = book->getDueDate();
    REQUIRE(bookDueDate.getDay() == 4);
    REQUIRE(bookDueDate.getMonth() == 2);
    REQUIRE(bookDueDate.getYear() == 2023);
  }
  SECTION("Testing borrowBook and returnBook function") {
    Member* member1 = new Member(500,"Ion","Chisinau","Ion@mail.ru");
    Book* book2 = new Book(100,"C#","John","Miller");
    Date* currentDate = Date::getCurrentDate();
    std::string capturedOutput = captureOutput([&] {book2->borrowBook(*member1,*currentDate);});
    REQUIRE(capturedOutput == "\"C#\" by John Miller was successfully borrowed to member with ID 500.");
    REQUIRE(member1->getBooksBorrowed().size() == 1);
    book2->returnBook();
    REQUIRE(member1->getBooksBorrowed().size() == 0);
    REQUIRE_THROWS_AS((book2->getDueDate()),std::logic_error);
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
  }
  SECTION("Testing getBooksBorrowed and setBooksBorrowed functions") {
    REQUIRE(memberNew1->getBooksBorrowed().size() == 0);
    memberNew1->setBooksBorrowed(bookNew);
    REQUIRE(memberNew1->getBooksBorrowed().size() == 1);
  }
}
template<typename Function>
void redirectFunction(Function func, const std::string& str) {
  std::stringstream input(str);
  std::streambuf* origCin = std::cin.rdbuf(input.rdbuf());
  func(str);
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

void extractOutput(std::string &str) {
  size_t startPos = str.find("\"");
  std::string extractedInfo;
  if (startPos != std::string::npos) {
    str = str.substr(startPos);
    std::cout << str << std::endl;
  }
}
