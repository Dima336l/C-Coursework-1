#include "Library.h"
#include <iomanip>


namespace MyNamespace {
  Library::Library(const std::string& fileName) : fileName(fileName) {
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
    std::cout << "Welcome to the library" << std::endl;
  }

  void Library::addBook(std::string line) {
    
  }

  void Library::printBooks(std::vector<std::vector<std::string>> cSVRows) {
    std::vector<int> columnWidths = {10,50,13,20,19};
    for (const auto& row : cSVRows) {
	for (size_t i = 0; i < row.size(); ++i) {
	  std::cout << std::setw(columnWidths[i]) << std::left << row[i];
	  
      }
	std::cout << std::endl; 
    }
  }
  
  void Library::addBooks(std::vector<std::vector<std::string>> cSVRows) {
    for (const auto& row : cSVRows) {
      std::string bookID = row[0];
      std::cout << bookID << std::endl; 
    }
  }
    
    


  void Library::handleLibrary() {
    std::vector<std::vector<std::string>> cSVRows = readFile();
    welcomeMessage();
    printBooks(cSVRows);
    addBooks(cSVRows);
  }
  
}
