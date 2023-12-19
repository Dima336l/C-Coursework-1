#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Person.h"
#include "Librarian.h"
#include "Date.h"

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
    REQUIRE_THROWS_AS(MyNamespace::Date(32,1,2000), std::invalid_argument);
    REQUIRE_THROWS_AS(MyNamespace::Date(1,13,2000), std::invalid_argument);
    REQUIRE_THROWS_AS(MyNamespace::Date(1,12,-10), std::invalid_argument);   
  }
  SECTION("Testing valid date values") {
    REQUIRE_NOTHROW(MyNamespace::Date(1,12,2000));
    REQUIRE_NOTHROW(MyNamespace::Date(5,3,1997));
    REQUIRE_NOTHROW(MyNamespace::Date(10,1,1000));
  }
  SECTION("Testing modification of date components") {
    MyNamespace::Date date(1,12,2000);
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
  SECTION("Testing leap year") {
    REQUIRE_NOTHROW(MyNamespace::Date(29,2,2024));
    REQUIRE_THROWS_AS(MyNamespace::Date(29,2,2022),std::invalid_argument);
  }
}
