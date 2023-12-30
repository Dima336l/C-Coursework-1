#include "Main.h"

using namespace std;
using namespace MyNamespace;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>" <<std::endl;
    return 1;
  }
  std::string fileName = argv[1];
  Library* library = new Library(fileName);
  library->handleLibrary();
  delete library;
  return 0;
}
