CXX = g++
CXXFLAGS = -g -Wall -Wextra -Wpedantic

.PHONY: all
all: program test clean

program: Main.cpp Date.o Book.o Person.o Member.o Librarian.o Menu.o Logic.o Global.o
	$(CXX) $(CXXFLAGS) -o Main Main.cpp Date.o Book.o Person.o Member.o Librarian.o Menu.o Logic.o Global.o

test: Test_main.cpp Date.o Book.o Person.o Member.o Librarian.o Global.o
	$(CXX) $(CXXFLAGS) -o Test_main Test_main.cpp Date.o Book.o Person.o Member.o Librarian.o Global.o

Global.o: Global.cpp Global.h
	$(CXX) $(CXXFLAGS) -c Global.cpp

Date.o: Date.cpp Date.h
	$(CXX) $(CXXFLAGS) -c Date.cpp

Book.o: Book.cpp Book.h
	$(CXX) $(CXXFLAGS) -c Book.cpp

Person.o: Person.cpp Person.h
	$(CXX) $(CXXFLAGS) -c Person.cpp

Member.o: Member.cpp Member.h
	$(CXX) $(CXXFLAGS) -c Member.cpp

Librarian.o: Librarian.cpp Librarian.h
	$(CXX) $(CXXFLAGS) -c Librarian.cpp

Menu.o: Menu.cpp Menu.h
	$(CXX) $(CXXFLAGS) -c Menu.cpp

Logic.o: Logic.cpp Logic.h
	$(CXX) $(CXXFLAGS) -c Logic.cpp

clean:
	$(RM) *.o


