#ifndef MYNAMESPACE_DATE_H
#define MYNAMESPACE_DATE_H

#include "MyNamespace.h"

namespace MyNamespace {
class Date {
 private:
  int day;
  int month;
  int year;
  static bool isValidDate(int d, int m, int y);
  static int daysInMonth(int m, int y);
  static bool isLeapYear(int y);
  int countDaysPassed();
  int countDaysRemaining();
 public:
  static Date* currentDate;
  Date(int d, int m, int y);
  Date(const Date& other);
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
};
}
#endif
