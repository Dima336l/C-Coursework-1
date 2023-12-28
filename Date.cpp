#include "MyNamespace.h"
#include "Date.h"
#include <iostream>
#include <stdexcept>

namespace MyNamespace {
  Date* Date::currentDate = nullptr;
  Date::Date(int d, int m, int y) {
    if (!Date::isValidDate(d,m,y)) {
      throw std::invalid_argument("Invalid date values");
    }
    day = d;
    month = m;
    year = y;
  }
  Date::Date(const Date& other) {
    day = other.getDay();
    month = other.getMonth();
    year = other.getYear();
  }
  
  
  int Date::getDay() const {
    return day;
  }
  int Date::getMonth() const {
    return month;
  }
  int Date::getYear() const {
    return year;
  }
  void Date::displayDate() const {
    std::cout << day << "/" << month << "/" << year << std::endl;
  }
  void Date::setDay(int d) {
    if (!isValidDate(d,month,year)) {
      throw std::invalid_argument("Invalid day value");
    }
    day = d;
  }
  void Date::setMonth(int m) {
    if (!isValidDate(day,m,year)) {
      throw std::invalid_argument("Invalid month value");
    }
    month = m;
  }
  void Date::setYear(int y) {
    if (!isValidDate(day,month,y)) {
      throw std::invalid_argument("Invalid year value");
    }
    year = y;
  }

  int Date::compareDates() const {
    Date currentDate = *Date::getCurrentDate();
    int day1 = currentDate.getDay();
    int month1 = currentDate.getMonth();
    int year1 = currentDate.getYear();
    if (year != year1)  {
      return (year > year1)? 1 : -1;
    } else if (month != month1) {
      return (month > month1) ? 1 : -1;
    } else {
      return (day > day1) ? 1 : ((day == day1) ? 0 : -1);
    }
  }
  
  void Date::setInitialDate() {
    int d,m,y;
    do {
    std::cout << "Enter day" << std::endl;
    std::cin >> d;
    std::cout << "Enter month" << std::endl;
    std::cin >> m;
    std::cout << "Enter year" << std::endl;
    std::cin >> y;
    } while (!isValidDate(d,m,y));
    currentDate = new Date(d,m,y);
  }
  Date* MyNamespace::Date::getCurrentDate() {
    return currentDate;
  }

  int Date::countDaysRemaining() {
    int daysRemaining = 0;
    Date currentDate = *Date::getCurrentDate();
    int day1 = day;
    int month1 = month;
    int year1 = year;
    int day2 = currentDate.getDay();
    int month2 = currentDate.getMonth();
    int year2 = currentDate.getYear();
     while (year2 < year1 || (year2 == year1 && (month2 < month1 || (month2 == month1 && day2 < day1)))) {
      daysRemaining++;
      day2++;
      if (day2 > Date::daysInMonth(month2,year2)) {
	day2 = 1;
	month2++;
	if (month2 > 12) {
	  month2 = 1;
	  year2++;
	}
      }
  }
     return daysRemaining;
  }
  
  int Date::countDaysPassed() {
    int daysPassed = 0;
    Date currentDate = *Date::getCurrentDate();
    int day1 = day;
    int month1 = month;
    int year1 = year;
    int days2 = currentDate.getDay();
    int month2 = currentDate.getMonth();
    int year2 = currentDate.getYear();
     while (year1 < year2 || (year1 == year2 && (month1 < month2 || (month1 == month2 && day1 < days2)))) {
      daysPassed++;
      day1++;
      if (day1 > Date::daysInMonth(month1,year1)) {
	day1 = 1;
	month1++;
	if (month1 > 12) {
	  month1 = 1;
	  year1++;
	}
      }
  }
     return daysPassed;
  }
  
  int Date::getDaysPassed(int hasPassed) {
    int daysPassed = 0;
    if (hasPassed == -1) {
      daysPassed =  this->countDaysPassed();
    } else if (hasPassed == 1) {
      daysPassed =  this->countDaysRemaining();
    }
    return daysPassed;
  }

  Date Date::addDays(int d) {
    if (isValidDate(day+d,month,year)) {
      day += d;
    } else {
      int remainingDays = d;
      year += (remainingDays / 365);
      remainingDays %= 365;
      while (remainingDays > 0) {
	int daysInMonth =Date::daysInMonth(month,year);
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
    return Date(day,month,year);
  }
  
  bool Date::isValidDate(int d, int m, int y) {
    if (y < 0 || m < 1 || m > 12 || d < 1 || d > Date::daysInMonth(m,y)) {
      return false;
  }
    return true;
  }

  int Date::daysInMonth(int m, int y) {
    static const int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int daysInMonth = days[m];
    if (m == 2 && Date::isLeapYear(y)) {
      daysInMonth = 29;
    }
    return daysInMonth;
  }

  bool Date::isLeapYear(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
  }

}
