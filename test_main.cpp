#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Person.h"

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
