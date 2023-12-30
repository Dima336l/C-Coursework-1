#include "MyNamespace.h"
#include "Date.h"


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

  void Date::handleInput(int& component, const std::string& prompt, const std::string& errorMessage) {
    while (true) {
        std::cout << prompt;
        std::cin >> component;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid input. Please enter an integer for the " << errorMessage << "." << std::endl;
            continue;
        }

        break;
    }
}
  
  void Date::setInitialDate() {
    int d,m,y;
    bool daySet = false;
    bool monthSet = false;
    bool yearSet = false;
    currentDate = new Date(1,12,2000);
    while (true) {
      if (!daySet) {
	std::cout << "Enter day: ";
	std::cin >> d;
	if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cerr << "Invalid input. Please enter an integer for the day." << std::endl;
                continue;  // Skip the rest of the loop and prompt for input again
            }
	try {
	  currentDate->setDay(d);
	  daySet = true;
	} catch (const std::invalid_argument& e) {
	  std::cerr << "Invalid argument: " << e.what() << std::endl;
	  continue;
	}
      }
       if (!monthSet) {
	std::cout << "Enter month: ";
	std::cin >> m;
	if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cerr << "Invalid input. Please enter an integer for the day." << std::endl;
                continue;  // Skip the rest of the loop and prompt for input again
            }
	try {
	  currentDate->setMonth(m);
	  monthSet = true;
	} catch (const std::invalid_argument& e) {
	  std::cerr << "Invalid argument: " << e.what() << std::endl;
	  continue;
	}
      }
        if (!yearSet) {
	std::cout << "Enter year: ";
	std::cin >> y;
	if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cerr << "Invalid input. Please enter an integer for the day." << std::endl;
                continue;  // Skip the rest of the loop and prompt for input again
            }
	try {
	  currentDate->setYear(y);
	  yearSet = true;
	} catch (const std::invalid_argument& e) {
	  std::cerr << "Invalid argument: " << e.what() << std::endl;
	  continue;
	}
      }

      if (std::cin.fail()) {
	std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cerr << "Invalid input. Please enter integers for day, month, and year." << std::endl;
	continue;
      }
      break;
    }
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
