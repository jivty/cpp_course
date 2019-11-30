#include "ortosegm.h"
#include <iostream>
#include <sstream>

bool testParse(const std::string& str) {
  std::istringstream istrm(str);
  OrtoSegm x;
  istrm >> x;
  if (istrm.good()) {
    std::cout << "Read success: " << str << " -> " << x << std::endl;
  }
  else {
    std::cout << "Read error: " << str << " -> " << x << std::endl;
  }
  return istrm.good();
}

void show(OrtoSegm segm) {
  std::cout << segm << ", length = " << segm.length() << std::endl;
}

void testContain(OrtoSegm segm, float x, float y) {
  std::cout << segm <<
    ((segm.contain(x, y)) ? " contains " : " doesn't contain ")
    << '(' << x << ',' << y << ')' << std::endl;
}

int main() {
  OrtoSegm test;
  try {
    OrtoSegm test1(1, 1, 2, 2);
  }
  catch (std::invalid_argument) {
    std::cout << "Not orto is catched" << std::endl;
  }
  OrtoSegm test2(1, 1, 1, 5);
  OrtoSegm test3(test2);
  std::cout << "Not orto is catched" << std::endl;
}