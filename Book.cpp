#include "Book.h"
#include "Global.h"

namespace MyNamespace {
  Book::Book(int bID, std::string bName, std::string authFirstN,std::string authLastN) {
    bookID = bID;
    bookName = bName;
    authorFirstName = authFirstN;
    authorLastName = authLastN;
    dueDateNotSet = true;
    dueDate = nullptr;
    borrower = nullptr;
  }
  Book::~Book() {
    delete borrower;
    delete dueDate;
  }
  std::string Book::getBookID() const {
    return std::to_string(bookID);
  }
  std::string Book::getBookName() {
    return bookName;
  }
  std::string Book::getAuthorFirstName() {
    return authorFirstName;
  }
  std::string Book::getAuthorLastName() {
    return authorLastName;
  }
  
  Date Book::getDueDate() {
    if (dueDateNotSet) {
      throw std::logic_error("Due date not set. Set it first.");
    }
    return *dueDate;
  }
  bool Book::checkIfDateSet() {
    return dueDateNotSet;
  }

  void Book::resetDaysSetFlag() {
    numOfDaysSet = true;
  }

  int Book::chooseAnotherDate() {
    int numOfDays = 0;
    std::cout << "How many days from today would you like the set the due date to be: ";
    std::string input;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Clearing input buffer.
    while (true) { 
      std::getline(std::cin,input);
      if (input.empty()) {
	std::cerr << "Input cannot be empty. Please enter a number: ";
	continue;
      }
      try {
	numOfDays = std::stoi(input);
      } catch (const std::invalid_argument &) {
	std::cerr << "Invalid input.Please enter an integer: ";
	continue;
      }	  
      if (numOfDays > 0){
	break;
      } else {
	std::cerr << "Invalid input. The number of days must be an integer greater than 0: ";
      }
    }
    return numOfDays;

  }

  int Book::determineNumOfDays() {
    char option;
    bool isChoiceNotValid;
    int numOfDays;
    std::cout<< std::endl << "Would you like to use the default due date which is 3 days from today or choose another date?" << std::endl;
    std::cout << "Enter 'Y' for custom date and 'N' for default: ";
    do {
      std::cin.get(option);
      isChoiceNotValid = (std::toupper(option) != 'Y' && std::toupper(option) != 'N');
      if (isChoiceNotValid) {
	std::cerr << "Invalid input, please enter 'Y' or 'N': ";
      }
    } while (isChoiceNotValid);
    if (std::toupper(option) == 'Y') {
      numOfDays = chooseAnotherDate();
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
      numOfDays = 3;
    }
    return numOfDays;
  }
  
  
  void Book::setDueDate(Date* currentDate) {
    Date newDueDate = *currentDate;
    if (!numOfDaysSet) { // Checking to see if the number of days has already been determined
      numOfDays = this->determineNumOfDays();
      numOfDaysSet = true;
    }
    newDueDate = newDueDate.addDays(numOfDays);
    dueDate = new Date(newDueDate);
    dueDateNotSet = false;
  }
  void Book::returnBook() {
    std::vector<Book*>& bookVec = borrower->getBooksBorrowed();
    auto it = std::find(bookVec.begin(),bookVec.end(),this);
    if (it != bookVec.end()) {
      bookVec.erase(it);
      delete dueDate;
      dueDate = nullptr;
      dueDateNotSet = true;
    }
  }
  
  void Book::borrowBook(Member &bur,Date due) {
    dueDate = new Date(due);
    bur.setBooksBorrowed(this);
    borrower = &bur;
    std::cout << std::endl;
    std::cout <<'"'<< bookName <<'"'<< " by " << authorFirstName << " " << authorLastName <<" was successfully borrowed to member with ID " << borrower->getMemberID() <<"."<< std::endl; 
  }
}



