#ifndef MENU_H
#define MENU_H
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
#include "Logic.h"
#include "Global.h"

namespace MyNamespace {
  class Logic;
  class Menu {
  private:
    Librarian* librarian;
    std::string fileName;
    Logic* logic;
  public:
    Menu(const std::string& fileName);
    void welcomeMessage();
    void displayBooks(std::vector<std::vector<std::string>> fileContent);
    void displayOptions();
    void handleMenu();
    void displayMembers();
    void displayBorrowedBooks();
  };
}

#endif
