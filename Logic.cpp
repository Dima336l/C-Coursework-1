#include "Logic.h"


namespace MyNamespace {
  class Menu;
  Logic::Logic(const std::string& fileName, Menu* m) : menu(m), fileName(fileName) {
    Date::currentDate = new Date(12,01,2024);  // Setting up a default currentDate
    librarian = new Librarian(1,"Dumitru","Colindale","Nircadmitrii@icloud.com",30000);
    initializeObjectMap(); // Creating an object map for later use for avoidance of repeating fine calculations
  }

  Logic::~Logic() {
    for (auto& book: books) {
      delete book;
    }
    books.clear();
    for (auto& member: members) {
      delete member;
    }
    members.clear();
    delete librarian;
    delete Date::currentDate;
  }

  void Logic::initializeObjectMap() {
    for (const auto& member: members) {
      objectMap[member] = false;  
    }
  }
  
  std::vector<std::vector<std::string>> Logic::readFile() {
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
      std::cerr << "Error opening the file." << std::endl;
    }
    std::vector<std::vector<std::string>> cSVRows;
    std::ifstream                         reader(fileName);
    if (reader.is_open()) {
      std::string line, column, id;
      /* Reading file line by line */
      while (std::getline(reader, line)) {
	std::stringstream        ss(line);
        std::vector<std::string> columns;
        bool                     withQ = false;
        std::string              part{""};
	/* Algorithm to handle commas inside CSV files */
        while (std::getline(ss, column, ',')) {
	  auto pos = column.find("\"");
	  if (pos < column.length()) {
	    withQ = !withQ;
	    part += column.substr(0, pos);
	    column = column.substr(pos + 1, column.length());
	  }
	  if (!withQ) {
	    column += part;
	    columns.emplace_back(std::move(column));
	    part = "";
	  } else {
	    part += column + ",";
	  }
        }
        cSVRows.emplace_back(columns);
      }
    }
    inputFile.close();
    return cSVRows;
  }

  void Logic::addBook(std::vector<std::vector<std::string>> cSVRows, int i) {
    /* Extracting the fields */
    int bookID = std::stoi(cSVRows[i][0]);
    std::string bookName = cSVRows[i][1];
    std::string authorFirstName = cSVRows[i][3];
    std::string authorLastName = cSVRows[i][4];
    Book* book = new Book(bookID,bookName,authorFirstName,authorLastName);
    books.push_back(book);
  }

  void Logic::addBooks(std::vector<std::vector<std::string>> cSVRows) {
    for (size_t i = 1; i < cSVRows.size();i++) {
      addBook(cSVRows,i);
    }
  }

  int Logic::getUserChoice() {
    int choice;
    std::string input;
    while (true) {
      std::getline(std::cin,input);
      if (input.empty()) {
	std::cerr << "Input cannot be empty. Please enter a number: ";
	continue;
      }
      try {
	choice = std::stoi(input);
	if (choice < 0 ) {
	  std::cerr<< "Input has to be a positive integer: ";
	  continue;
	}
	break;
      } catch(const std::invalid_argument &) {
	std::cerr << "Invalid input. Please enter a valid integer for your choice: ";
      }
    }

    return choice;
  }

  void Logic::handleBookIssue() {
    std::cout << "Enter book ID: ";
    int bookID = getUserChoice();
    std::cout << "Enter member ID: ";
    int memberID = getUserChoice();
    try {
      librarian->issueBook(memberID,bookID);
    } catch(const std::runtime_error& e) {
      std::cerr <<  e.what() << std::endl;
    }
  }
  void Logic::handleReturn() {
    std::cout << "Enter book ID: ";
    int bookID = getUserChoice();
    std::cout << "Enter member ID: ";
    int memberID = getUserChoice();
    std::cout << std::endl;
    try {
      librarian->returnBook(memberID,bookID);
    } catch(const std::runtime_error& e) {
      std::cerr << e.what() << std::endl;
    }
  }

  void Logic::addMember() {
    librarian->addMember();
  }

  void Logic::changeDate() {
    std::cout << "Please enter the new date: " << std::endl;
    Date::setInitialDate();
  }

  void Logic::displayBooks(std::vector<std::vector<std::string>> cSVRows) {
    menu->displayBooks(cSVRows);
  }

  void Logic::displayMembers() {
    menu->displayMembers();
  }

  void Logic::displayBorrowedBooks() {
    menu->displayBorrowedBooks();
  }
  
  void Logic::handleMenu(std::vector<std::vector<std::string>> cSVRows) {
    int choice;
    do {
      menu->displayOptions();
      std::cout << "Enter your choice: ";
      choice = getUserChoice();
      if (choice >= 1 && choice <= 8) {
	std::cout << std::endl;
      }
      switch(choice) {
      case 1:
	displayBooks(cSVRows);
	break;
      case 2:
        displayMembers();
	break;
      case 3:
        addMember();
	break;
      case 4:
        handleBookIssue();
	break;
      case 5:
        handleReturn();
	break;
      case 6:
        displayBorrowedBooks();
	break;
      case 7:
        changeDate();
	break;
      case 8:
	std::cout << "Goodbye." << std::endl;
	break;
      default:
	std::cout <<"Invalid choice, please enter a number between 1 and 8." << std::endl;
	break;
      }
    } while (choice != 8);
  }

  void Logic::handleLogic() {
    std::vector<std::vector<std::string>> fileContents = Logic::readFile();
    addBooks(fileContents);
    handleMenu(fileContents);
    
  }
}
