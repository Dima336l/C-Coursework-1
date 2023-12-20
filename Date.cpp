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
  MyNamespace::Date MyNamespace::Date::addDays(int d) {
    if (isValidDate(day+d,month,year)) {
      day += d;
    } else {
      int remainingDays = d;
      year += (remainingDays / 365);
      remainingDays %= 365;
      while (remainingDays > 0) {
	int daysInMonth = Date::daysInMonth(month,year);
	if (remainingDays > daysInMonth - day ) {
	  remainingDays = remainingDays - (daysInMonth - day );
	  month ++;
      if (month > 12) {
	month = 1;
	year++;
      }
      day = 0;
	} else {
	day += remainingDays;
	remainingDays = 0;
	}
      }
    }
    return MyNamespace::Date(day,month,year);
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

