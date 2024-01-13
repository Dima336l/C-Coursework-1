#ifndef LOGIC_H
#define LOGIC_H

#include "MyNamespace.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "MyNamespace.h"
#include "Date.h"
#include "Person.h"
#include "Member.h"
#include "Book.h"
#include "Librarian.h"
#include "Menu.h"
#include "Global.h"

namespace MyNamespace {
  class Menu;
  class Logic {
  private:
    Librarian* librarian;
    Menu* menu;
    std::string fileName;
  public :
    Logic(const std::string& fileName, Menu* m);
    ~Logic();
    void addBooks(std::vector<std::vector<std::string>> fileContent);
    void addBook(std::vector<std::vector<std::string>>, int i);
    void handleMenu(int choice);
    std::vector<std::vector<std::string>> readFile();
    void addMember();
    void handleBookIssue();
    void handleReturn();
    void changeDate();
    void initializeObjectMap();
    void displayBooks(std::vector<std::vector<std::string>> cSVRows);
    void displayMembers();
    void handleMenu(std::vector<std::vector<std::string>> cSVRows);
    void handleLogic();
    void displayBorrowedBooks();
    int getUserChoice();
  };
}

#endif
