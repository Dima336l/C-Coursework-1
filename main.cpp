#include "Main.h"

using namespace std;
using namespace MyNamespace;

int main(int argc, char *argv[]) {
  if (argc != 2) { // Checking if the usage is correct, argv[2] represents the second parameter when compiling
    std::cerr << "Usage: " << argv[0] << " <filename>" <<std::endl;
    return 1; // Exiting if error encountered
  }
  std::string fileName = argv[1]; // Extracting the filename from the compilation command
  Library* library = new Library(fileName); // Passing the extracted filename to the library class constructor
  library->handleLibrary();
  return 0;
}
