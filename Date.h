#ifndef DATE_H
#define DATE_H

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
  Date(int d, int m, int y);
  Date addDays(int d);
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
