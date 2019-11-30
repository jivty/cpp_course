#include "ortoregt.h"
#include <iostream>
#include <sstream>

bool testParse(const std::string& str) {
  std::istringstream istrm(str);
  OrtoRegt x;
  istrm >> x;
  if (istrm.good()) {
    std::cout << "Read success: " << str << " -> " << x << std::endl;
  } else {
    std::cout << "Read error: " << str << " -> " << x << std::endl;
  }
  return istrm.good();
}

void show(OrtoRegt regt) {
  std::cout << regt << ", high = " << regt.high()
    << ", wigth = " << regt.width() << std::endl;
}

void testContain(OrtoRegt regt, float x, float y) {
  std::cout << regt <<
    ((regt.contain(x, y)) ? " contains " : " doesn't contain ")
    << '(' << x << ',' << y << ')' << std::endl;
}

int main() {
  OrtoRegt test;
  show(test);
  test = OrtoRegt(0, 0, 0, 0);
  OrtoRegt test2(12, 0, 1, 2);
  show(test2);
  OrtoRegt test3(test2);
  show(test3);
  OrtoRegt test4(0, 20, 20, 0);
  show(test4);
  test4.move(1, -1);
  testContain(test4, 1, -1);
  testContain(test4, 5, 20);
  testContain(test4, 4, 4);
  testContain(test, std::numeric_limits<float>::epsilon(), std::numeric_limits<float>::epsilon());
  testParse("box:(2,0)(0,3)");
  testParse("box :(2,0)(0,3)");
  testParse("box:   (2,0)(0,3)");
  testParse("box:( 2, 0)( 0, 3)");
  return 0;
}