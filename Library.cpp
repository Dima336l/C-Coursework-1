#include "Library.h"



namespace MyNamespace {
  Library::Library(const std::string& fileName) : fileName(fileName) {
    Date::setInitialDate();
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
    std::cout << "Welcome to the library" << std::endl;
  }

  void Library::addBook(std::vector<std::vector<std::string>> cSVRows, int i) {
    int bookID = std::stoi(cSVRows[i][0]);
    std::string bookName = cSVRows[i][1];
    std::string authorFirstName = cSVRows[i][3];
    std::string authorLastName = cSVRows[i][4];
    Book* book = new Book(bookID,bookName,authorFirstName,authorLastName);
    books.push_back(book);
  }

  void Library::printBooks(std::vector<std::vector<std::string>> cSVRows) {
    std::vector<int> columnWidths = {10,50,13,20,19};
    for (int i = 0; i < cSVRows.size();i++) {
      for (size_t j = 0; j < cSVRows[i].size(); ++j) {
	std::cout << std::setw(columnWidths[j]) << std::left << cSVRows[i][j];
      }
      std::cout << std::endl; 
    }
  }
  
  void Library::addBooks(std::vector<std::vector<std::string>> cSVRows) {
    for (int i = 1; i < cSVRows.size();i++) {
      addBook(cSVRows,i);
    }
    std::cout << "Books size vector after addBooks " << books.size() << std::endl;
  }

  void Library::addMember() {
   
  }

  void Library::displayOptions() {
    std::cout << "1. Add a member" << std::endl;
    std::cout << "2. Issue a book" << std::endl;
    std::cout << "3. Return a book" << std::endl;
    std::cout << "4. Display books borrowed" << std::endl;
    std::cout << "5. Calculate fine" << std::endl;
  }

  void Library::handleMenu() {
    
  }
    


  void Library::handleLibrary() {
    /*std::vector<std::vector<std::string>> cSVRows = readFile();
    welcomeMessage();
    addBooks(cSVRows);
    librarian->addMember();*/
 
  }
  
}
