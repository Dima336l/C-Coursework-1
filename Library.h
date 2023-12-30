#ifndef LIBRARY_H
#define LIBRARY_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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
    void addBook(std::string line);
    std::vector<std::vector<std::string>> readFile();
    void welcomeMessage();
    void printBooks(std::vector<std::vector<std::string>> fileContent);
  private:
    std::string fileName;
  };
}

#endif
