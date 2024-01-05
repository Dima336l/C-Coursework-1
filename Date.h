#ifndef MYNAMESPACE_DATE_H
#define MYNAMESPACE_DATE_H

#include "MyNamespace.h"
#include <iostream>
#include <stdexcept>
#include <limits>
#include <sstream>
#include <string>

namespace MyNamespace {
class Date {
 private:
  int day;
  int month;
  int year;
  static bool isValidDate(int d, int m, int y);
  static int daysInMonth(int m, int y);
  static bool isLeapYear(int y);
 public:
  int countDaysPassed();
  int countDaysRemaining();
  static Date* currentDate;
  Date(int d, int m, int y);
  Date(const Date& other);
  Date& operator=(const Date& other) = default;
  Date addDays(int d);
  static void setInitialDate();
  static Date* getCurrentDate();
  int compareDates () const;
  int getDaysPassed(int compareDates);
  int getDay() const;
  int getMonth() const;
  int getYear() const;
  void setDay(int d);
  void setMonth(int m);
  void setYear(int y);
  void displayDate() const;
  bool handleInput(int& component, const std::string& errorMessage);
};
}
#endif
