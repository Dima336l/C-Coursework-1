#include "Library.h"



namespace MyNamespace {
  Library::Library(const std::string& fileName) : fileName(fileName) {
    welcomeMessage();
    Date::currentDate = new Date(1,12,200);
    //Date::setInitialDate();
    Member* member1 = new Member(1,"Dumitru","Colindale","Nircadmitrii@icloud.com");
    Member* member2 = new Member(2,"Andrei","Colindale","AndreiNirca@mail.ru");
    members.push_back(member1);
    members.push_back(member2);
    librarian = new Librarian(1,"Dumitru","Colindale","Nircadmitrii@icloud.com",30000);
  }
  std::vector<std::vector<std::string>> Library::readFile() {
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
      std::cerr << "Error opening the file." << std::endl;
    }
    std::vector<std::vector<std::string>> cSVRows;
    std::ifstream                         reader(fileName);
    if (reader.is_open()) {
      std::string line, column, id;
      while (std::getline(reader, line)) {
	std::stringstream        ss(line);
        std::vector<std::string> columns;
        bool                     withQ = false;
        std::string              part{""};
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
  
  void Library::welcomeMessage() {
    std::cout << std::endl;
    std::cout << "Welcome to the library" << std::endl << std::endl;
    std::cout <<"Please enter today's date" << std::endl;
  }

  void Library::addBook(std::vector<std::vector<std::string>> cSVRows, int i) {
    int bookID = std::stoi(cSVRows[i][0]);
    std::string bookName = cSVRows[i][1];
    std::string authorFirstName = cSVRows[i][3];
    std::string authorLastName = cSVRows[i][4];
    Book* book = new Book(bookID,bookName,authorFirstName,authorLastName);
    books.push_back(book);
  }

  void Library::displayBooks(std::vector<std::vector<std::string>> cSVRows) {
    std::vector<int> columnWidths = {10,50,13,20,19};
    for (int i = 0; i < cSVRows.size();i++) {
      for (size_t j = 0; j < cSVRows[i].size(); ++j) {
	std::cout << std::setw(columnWidths[j]) << std::left << cSVRows[i][j];
      }
      std::cout << std::endl; 
    }
  }

  void Library::displayMembers() {
    if (members.size() == 0) {
      std::cout << "There are no members registered in the system." << std::endl;
    }
    else {
      std::cout << std::setw(5) << std::left << "ID";
      std::cout << std::setw(15) << std::left << "Name";
      std::cout << std::setw(15) << std::left << "Address";
      std::cout << "Email" << std::endl;
      for (const auto& member: members) {
	std::cout << std::setw(5) << std::left << member->getMemberID();
	std::cout << std::setw(15) << std::left << member->getName();
	std::cout << std::setw(15) << std::left << member->getAddress();
	std::cout << member->getEmail() << std::endl;
      }
    }
  }
  
  void Library::addBooks(std::vector<std::vector<std::string>> cSVRows) {
    for (int i = 1; i < cSVRows.size();i++) {
      addBook(cSVRows,i);
    }
  }

  void Library::displayOptions() {
    std::cout << std::endl;
    std::cout << "1. Display books" << std::endl;
    std::cout << "2. Display members" << std::endl;
    std::cout << "3. Add a member" << std::endl;
    std::cout << "4. Issue a book" << std::endl;
    std::cout << "5. Return a book" << std::endl;
    std::cout << "6. Display books borrowed" << std::endl;
    std::cout << "7. Calculate fine" << std::endl;
    std::cout << "8. Change date" << std::endl;
    std::cout << "9. Exit" << std::endl << std::endl;
  }

  int Library::getUserChoice() {
    int choice;
    std::string input;
    while (true) {
      std::getline(std::cin,input);
      if (input.empty()) {
	std::cerr << "Input cannot be empty. Please enter a number." << std::endl;
	continue;
      }
      try {
	choice = std::stoi(input);
	break;
      } catch(const std::invalid_argument &) {
	std::cerr << "\nInvalid input. Please enter a valid integer for your choice." << std::endl;
	displayOptions();
	std::cout << "Enter your choice: ";
      }
    }

    return choice;
  }

  void Library::handleBookIssue() {
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
  void Library::handleReturn() {
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

  void Library::addMember() {
    librarian->addMember();
  }
  

  void Library::handleMenu(std::vector<std::vector<std::string>> cSVRows) {
    int choice;
    do {
      displayOptions();
      std::cout << "Enter your choice: ";
      choice = getUserChoice();
      std::cout << std::endl;
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
	std::cout << "You entered Option 6." << std::endl;
	break;
      case 7:
	std::cout << "You entered Option 7." << std::endl;
	break;
      case 8:
	std::cout << "You entered Option 8." << std::endl;
	break;
      case 9:
	std::cout << "Goodbye." << std::endl;
	break;
      default:
	std::cout <<"Invalid choice, please enter a number between 1 and 7." << std::endl;
	break;
      }
    } while (choice != 9);
  }

    


  void Library::handleLibrary() {
    std::vector<std::vector<std::string>> cSVRows = readFile();
    addBooks(cSVRows);
    handleMenu(cSVRows);
    
 
  }
  
}
