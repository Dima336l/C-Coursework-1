#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Person.h"
#include "Librarian.h"

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
