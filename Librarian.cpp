#include "Librarian.h"


namespace MyNamespace {
  Librarian::Librarian(int staffID, std::string name, std::string address, std::string email, int sal) {
    setName(name);
    setAddress(address);
    setEmail(email);
    Librarian::setStaffID(staffID);
    Librarian::setSalary(sal);
  }

  void Librarian::setStaffID(int id) {
    staffId = id;
  }

  void Librarian::setSalary(int sal) {
    salary = sal;
  }

  int Librarian::getStaffID() {
    return staffId;
  }

  int Librarian::getSalary() {
    return salary;
  }
  void Librarian:: resetFineSetFlag() {
    fineSet = false;
  }
  bool Librarian::isValidEmail(const std::string& email) {
    const std::regex emailRegex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return std::regex_match(email, emailRegex);
  }

  bool Librarian::containsOnlyAlphabet(const std::string& str) {
    return std::all_of(str.begin(),str.end(),::isalpha);
  }

  std::string Librarian::getMemberName() {
    std::string name;
    while (true) {
      std::cout << "Enter member name: ";
      std::getline(std::cin, name);
      if (containsOnlyAlphabet(name)) {
	if (name.empty()) {
	  throw std::runtime_error ("Name cannot be empty.");
	} else {
	  break;
	}
      } else {
	throw std::runtime_error ("Invalid input. Member name should only contain leters.");
      }
    }
    return name;
  }

  std::string Librarian::getMemberAddress() {
    std::string address;
    while (true) {
      std::cout << "Enter member adress: ";
      std::getline(std::cin, address);
      if (!address.empty()) {
	break;
      } else {
	throw std::runtime_error ("Invalid input. Address cannot be empty.");
      }
    }
    return address;
  }

  std::string Librarian::getMemberEmail() {
    std::string email;
    while (true) {
      std::cout << "Enter email: ";
      std::getline (std::cin,email);
      if (email.empty()) {
	throw std::runtime_error ("Email cannot be empty.");
      }
      else if (Librarian::isValidEmail(email)) {
	if (std::find_if(members.begin(),members.end(),[&email](Member* m) { return m->getEmail() == email; }) == members.end())  {
	  break;
	}else {
	  throw std::runtime_error ("A member with this email is already registered.");
	} 
      } else {
	throw std::runtime_error ("Invalid email format. Please enter valid email.");
      }
    }
    return email;
  }
  void Librarian::addMember() {
    std::string memberName,memberAddress,memberEmail;
    bool nameSet = false;
    bool addressSet = false;
    bool emailSet = false;
    int memberId = members.size() + 1;
    while (true) {
      try {
	if (!nameSet) {
	  memberName = Librarian::getMemberName();
	  nameSet = true;
	}
	if (!addressSet) {
	  memberAddress = Librarian::getMemberAddress();
	  addressSet = true;
	}
	if (!emailSet) {
	  memberEmail = Librarian::getMemberEmail();
	  emailSet = true;
	}
	std::cout << std::endl;
	std::cout << "The member with the following details was successfully registered." << std::endl;
	std::cout << "ID: " << memberId << std::endl;
	std::cout << "Name: " << memberName << std::endl;
	std::cout << "Address: " << memberAddress <<std::endl;
	std::cout << "Email: " << memberEmail << std::endl;
	Member* member = new Member(memberId,memberName,memberAddress,memberEmail);
	members.push_back(member);
	break;
      }
      catch (const std::runtime_error& e) {
	std::cerr << e.what() << std::endl;
      }
    }
  }


  std::vector<Member*>::iterator Librarian::findMemberByID(int memberID) {
    auto it = std::find_if(members.begin(), members.end(),
			   [memberID](const Member* m) {
			     return m->getMemberID() == std::to_string(memberID);
			   });
    return it;
  } 

  std::vector<Book*>::iterator Librarian::findBookByID(int bookID) {
    auto it = std::find_if(books.begin(), books.end(),
			   [bookID](const Book* b) {
			     return b->getBookID() == std::to_string(bookID);
			   });
    return it;
  }

  void Librarian::handleBookIssue(std::vector<Member*>::iterator& memberit, std::vector<Book*>::iterator& bookit,int memberID, int bookID) {
    Date* currentDate = Date::getCurrentDate();
    (*bookit)->setDueDate(currentDate);
    Date bookDueDate = (*bookit)->getDueDate();
    (*bookit)->borrowBook(**memberit,bookDueDate);
  }

  bool Librarian::handleMemberIt(std::vector<Member*>::iterator memberit,int memberID) {
    if (memberit == members.end()) {
      throw std::runtime_error("\nMember with ID " +  std::to_string(memberID) +  " was not found.");
      return true;
    }
    return false;
  }

  bool Librarian::handleBookIt(std::vector<Book*>::iterator bookit,int bookID) {
    if (bookit == books.end()) {
      throw std::runtime_error ("\nBook with ID " + std::to_string(bookID) + " was not found.");
      return true;
    }
    return false;
  }


  void Librarian::issueBook(int memberID, int bookID) {
    auto memberit = Librarian::findMemberByID(memberID);
    auto bookit = Librarian::findBookByID(bookID);
    if ((Librarian::handleMemberIt(memberit,memberID)) || (Librarian::handleBookIt(bookit,bookID))) {
      return;
    }
    if (((*bookit)->checkIfDateSet())) {
      Librarian::handleBookIssue(memberit,bookit,memberID,bookID);
    }else {
      throw std::runtime_error("Book with name \"" + (*bookit)->getBookName() + "\" is already borrowed my another member.");
    }
  }
  
  void Librarian::handleBookReturn(std::vector<Member*>::iterator& memberit, std::vector<Book*>::iterator& bookit, int memberID, int bookID) {
    std::cout <<'"'<<(*bookit)->getBookName() <<'"'<< " by " <<(*bookit)->getAuthorFirstName() << " " << (*bookit)->getAuthorLastName()  << " was successfully returned by member with ID " << memberID <<"."<< std::endl;
    (*bookit)->returnBook();
  }
  
  void Librarian::returnBook(int memberID,int bookID) {
    auto memberit = Librarian::findMemberByID(memberID);
    auto bookit = Librarian::findBookByID(bookID);
    if ((Librarian::handleMemberIt(memberit,memberID)) || (Librarian::handleBookIt(bookit,bookID))) {
      return;
    }
    const std::vector <Book*>& booksBorrowed = (*memberit)->getBooksBorrowed();
    bool bookFound = false;
    for (const Book* book : booksBorrowed) {
      if (book->getBookID() == std::to_string(bookID)) {
	bookFound = true;
	break;
      }
    }
    if (bookFound) {
      Librarian::calcFine(memberID);
      Librarian::handleBookReturn(memberit,bookit,memberID,bookID);
    } else {
      throw std::runtime_error("Member with ID " + ((*memberit)->getMemberID()) + " did not borrow book with ID " + std::to_string(bookID) +".");
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
  }

  
  void Librarian::calcFineForOneBook(Book* book,int finePerDay) {
    Date* currentDate = Date::getCurrentDate();
    Date bookDueDate = book->getDueDate();
    int dateComparasion = bookDueDate.compareDates();
    int daysPassed = bookDueDate.getDaysPassed(dateComparasion);
    if (daysPassed != 0) {
      std::string dayStr = (daysPassed == 1) ? "day" : "days";
      if (dateComparasion == -1) {
	std::cout <<std::endl<<'"'<< book->getBookName() <<'"' <<" by " << book->getAuthorFirstName() << " " << book->getAuthorLastName() << " is " << daysPassed << " " << dayStr <<" past its due date." << std::endl;
	std::cout << "The amount you owe to the library is " << daysPassed*finePerDay << "£." << std::endl;
      } else if (dateComparasion == 1) {
	std::cout <<std::endl<< '"' << book->getBookName() << '"' << " by " << book->getAuthorFirstName() << " " << book->getAuthorLastName() << " is due in " << daysPassed << " " << dayStr << ". Nothing is owed to the library." << std::endl;
      }   
    } else {
      std::cout << "The book is due today." << std::endl;
    }
  }

  int Librarian::determineFine() {
    char option;
    bool isChoiceNotValid;
    std::cout << "Would you like to use the default fine of 1£ or would you like to set up a custom amount?" << std::endl;
    do {
      std::cout << "Enter 'Y' for custom amount and 'N' for default: ";
      std::cin.get(option);
      isChoiceNotValid = (std::toupper(option) != 'Y' && std::toupper(option) != 'N');
      if (isChoiceNotValid) {
        throw std::runtime_error("Invalid input, please enter 'Y' or 'N'");
      }
    } while (!isChoiceNotValid);
    if (std::toupper(option) == 'Y') {
      while (true) {
	std::cout << "Please set the fine rate: ";
        if (std::cin >> finePerDay && finePerDay > 0){
	  break;
	} else {
	  std::cin.clear();
	  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
	  throw std::runtime_error ("Invalid input. The fine must be an integer greater than 0");
	}
      }
    } else {
      finePerDay = 1;
    }
    return finePerDay;
  }
  
  void Librarian::calcFine(int memberID){
    auto memberit = Librarian::findMemberByID(memberID);
    if (Librarian::handleMemberIt(memberit,memberID)) {
      return;
    }
    const auto& borrowedBooks = (*memberit)->getBooksBorrowed();
    if (!fineSet) {
      finePerDay = Librarian::determineFine();
      fineSet = true;
    }
  
    for (const auto& book: borrowedBooks) {
      Librarian::calcFineForOneBook(book,finePerDay);
    }
  }
  
  void Librarian::displayBorrowedBooks(int memberID) {
    auto memberit = Librarian::findMemberByID(memberID);
    if (Librarian::handleMemberIt(memberit,memberID)) {
      return;
    }
    const auto& borrowedBooks = (*memberit)->getBooksBorrowed();
    if (borrowedBooks.size() == 0) {
      throw std::runtime_error ("Member with ID " + std::to_string(memberID) + " has no books borrowed.");
    }else {
      int counter = 0;
      std::cout << "[";
      for (const auto& book: borrowedBooks) {
	std::string comma = (counter == borrowedBooks.size() - 1) ? "" : ", ";
	std::cout <<'"'<<book->getBookName() <<'"'<< " by " <<book->getAuthorFirstName() << " " << book->getAuthorLastName() << comma;
	counter++;
      }
      std::cout << "]" << std::endl;
    }
  }
}
