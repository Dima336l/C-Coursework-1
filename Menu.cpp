#include "Menu.h"


namespace MyNamespace {
  Menu::Menu(const std::string& fileName) : fileName(fileName) { // Passing the filename as a parameter in the constructor to handle different CSV files
    logic = new Logic(fileName,this);
  }
  
 
  void Menu::welcomeMessage() {
    std::cout << std::endl;
    std::cout << "Welcome to the library" << std::endl;
  }


  void Menu::displayBooks(std::vector<std::vector<std::string>> cSVRows) {
    std::vector<int> columnWidths = {10,50,13,20,19}; // Parameters for string formatting
    for (size_t i = 0; i < cSVRows.size();i++) {
      for (size_t j = 0; j < cSVRows[i].size(); ++j) {
	std::cout << std::setw(columnWidths[j]) << std::left << cSVRows[i][j];
      }
      std::cout << std::endl; 
    }
  }

  void Menu::displayMembers() {
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
  
  void Menu::displayOptions() {
    std::cout << std::endl;
    std::cout <<"\t\t\t\t" << Date::currentDate->displayDate() << std::endl;
    std::cout << "1. Display books" << std::endl;
    std::cout << "2. Display members" << std::endl;
    std::cout << "3. Add a member" << std::endl;
    std::cout << "4. Issue a book" << std::endl;
    std::cout << "5. Return a book" << std::endl;
    std::cout << "6. Display books borrowed" << std::endl;
    std::cout << "7. Change date" << std::endl;
    std::cout << "8. Exit" << std::endl << std::endl;
  }


  void Menu::displayBorrowedBooks() {
    std::cout << "Enter member ID: ";
    int memberID = logic->getUserChoice();
    std::cout << std::endl;
    librarian->displayBorrowedBooks(memberID);
    
  }

  void Menu::handleMenu() {
    logic->handleLogic();
  }

}
