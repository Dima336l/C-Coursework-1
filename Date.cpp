#include "Date.h"
#include <iostream>
#include <stdexcept>

namespace MyNamespace {
  Date::Date(int d, int m, int y) {
    if (!Date::isValidDate(d,m,y)) {
      throw std::invalid_argument("Invalid date values");
    }
    day = d;
    month = m;
    year = y;
  }
  int MyNamespace::Date::getDay() const {
    return day;
  }
  int MyNamespace::Date::getMonth() const {
    return month;
  }
  int MyNamespace::Date::getYear() const {
    return year;
  }
  void MyNamespace::Date::displayDate() const {
    std::cout << day << "/" << month << "/" << year << std::endl;
  }
  void MyNamespace::Date::setDay(int d) {
    if (!isValidDate(d,month,year)) {
      throw std::invalid_argument("Invalid day value");
    }
    day = d;
  }
  void MyNamespace::Date::setMonth(int m) {
    if (!isValidDate(day,m,year)) {
      throw std::invalid_argument("Invalid month value");
    }
    month = m;
  }
  void MyNamespace::Date::setYear(int y) {
    if (!isValidDate(day,month,y)) {
      throw std::invalid_argument("Invalid year value");
    }
    year = y;
  }
  bool MyNamespace::Date::isValidDate(int d, int m, int y) {
    if (y < 0 || m < 1 || m > 12 || d < 1 || d > Date::daysInMonth(m,y)) {
      return false;
  }
    return true;
  }

  int MyNamespace::Date::daysInMonth(int m, int y) {
    static const int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int daysInMonth = days[m];
    if (m == 2 && isLeapYear(y)) {
      daysInMonth = 29;
    }
    return daysInMonth;
  }

  bool MyNamespace::Date::isLeapYear(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
  }

}

