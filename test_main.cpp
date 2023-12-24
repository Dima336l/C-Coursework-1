#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "MyNamespace.h"
#include "Date.h"
#include "Person.h"
#include "Librarian.h"
#include "Book.h"
#include "Member.h"
#include <vector>

using namespace MyNamespace;

TEST_CASE("Person class tests", "[PERSON]") {
  SECTION("Test default constructor and getters") {
    Person p;
    REQUIRE(p.getName() == "");
    REQUIRE(p.getAddress() == "");
    REQUIRE(p.getEmail() == "");
  }

  SECTION ("Test setters and getters") {
    Person p;
    p.setName("Dumitru");
    p.setAddress("Colindale");
    p.setEmail("Nircadmitrii@icloud.com");
    REQUIRE(p.getName() == "Dumitru");
    REQUIRE(p.getAddress() == "Colindale");
    REQUIRE(p.getEmail() == "Nircadmitrii@icloud.com");
  }
}

TEST_CASE("Librarian class tests", "[Librarian]") {
  SECTION("Test default constructor and getters") {
    Librarian lib;
    REQUIRE(lib.getName() == "");
    REQUIRE(lib.getAddress() == "");
    REQUIRE(lib.getEmail() == "");
    REQUIRE(lib.getStaffID() == 0);
    REQUIRE(lib.getSalary() == 0);
  }
  SECTION("Test parameterized constructor and getters") {
    Librarian lib(1,"Dumitru","Colindale","Nircadmitrii@icloud.com",30000);
    REQUIRE(lib.getName() == "Dumitru");
    REQUIRE(lib.getAddress() == "Colindale");
    REQUIRE(lib.getEmail() == "Nircadmitrii@icloud.com");
    REQUIRE(lib.getStaffID() == 1);
    REQUIRE(lib.getSalary() == 30000);
  } 
}

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
  SECTION("Testing initial date value") {
    Date currentDate = Date::getCurrentDate();
    REQUIRE(currentDate.getDay() == 1);
    REQUIRE(currentDate.getMonth() == 1);
    REQUIRE(currentDate.getYear() == 2000);
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
  Date bookDueDate(4,2,2023);
  int daysPassed = bookDueDate.getDaysPassed();
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

	 
