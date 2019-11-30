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

void showIntersection(OrtoSegm lhs, OrtoSegm rhs) {
  OrtoSegm intrsct(intersect(lhs, rhs));
  std::cout << lhs << " intersect " << rhs << " -> " << intrsct << std::endl;
}

int main() {
  constexpr float eps(std::numeric_limits<float>::epsilon());
  try {
    OrtoSegm testNotOrto(0, 0, 2*eps, 2*eps);
  }
  catch (std::invalid_argument) {
    std::cout << "Not orto is catched" << std::endl;
  }
  std::cout << std::endl;
  OrtoSegm test;
  show(test);
  test = OrtoSegm(0, 0, 0, 0);
  OrtoSegm test2(12, 0, 1, 0);
  show(test2);
  OrtoSegm test3(test2);
  show(test3);
  OrtoSegm test4(-1, 19, 19, 19);
  show(test4);
  std::cout << std::endl;
  std::cout << "move(1,-1) " << test4 << " -> ";
  show(test4.move(1, -1));
  std::cout << std::endl;
  testContain(test4, 1, -1);
  testContain(test2, 1, 0);
  testContain(test3, 5, 0);
  testContain(test, eps, eps);
  std::cout << std::endl;
  testParse("segm:(2,0)(2,3)");
  testParse("segm :(2,0)(2,3)");
  testParse("segm:   (2,0)(2,3)");
  testParse("segm:( 2, 0)( 2, 3)");
  std::cout << std::endl;
  OrtoSegm test5(4, -4, 4, 4);
  showIntersection(test, test4);
  showIntersection(test2, test5);
  OrtoSegm test6(test5);
  showIntersection(test5, test6.move(0, 1));
}