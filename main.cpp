#include "Person.h"
#include <iostream>

using namespace std;

int main() {
  Person p;
  p.setName("Dumitru");
  cout << p.getName() << endl;
  return 0;
}
