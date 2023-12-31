#ifndef LIBRARY_H
#define LIBRARY_H
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
#include "Global.h"

namespace MyNamespace {
  class Library {
  public:
    Library(const std::string& fileName);
    void handleLibrary();
    void addBooks(std::vector<std::vector<std::string>> fileContent);
    void addBook(std::vector<std::vector<std::string>>, int i);
    std::vector<std::vector<std::string>> readFile();
    void welcomeMessage();
    void displayBooks(std::vector<std::vector<std::string>> fileContent);
    void addMember();
    void displayOptions();
    void handleMenu(std::vector<std::vector<std::string>> fileContent);
    void displayMembers();
    void handleBookIssue();
    void handleReturn();
    void displayBorrowedBooks();
    void changeDate();
    int getUserChoice();
  private:
    Librarian* librarian;
    std::string fileName;
  };
}

#endif
