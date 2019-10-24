#include "rational.h"
#include <iostream>
#include <sstream>

bool testParse(const std::string& str) {
  std::istringstream istrm(str);
  Rational z;
  istrm >> z;
  if (istrm.good()) {
    std::cout << "Read succes:" << str << " -> " << z << std::endl;
  } else {
    std::cout << "Read error:" << str << " -> " << z << std::endl;
  }
  return istrm.good();
}

int main() {
  Rational z, b;
  std::cout << "z = " << z << std::endl;
  z = 4;
  std::cout << "z = 4 : z -> " << z << std::endl;
  z = Rational(4, 2);
  std::cout << "z = 4/2 : z -> " << z << std::endl;
  b = Rational(z);
  std::cout << z << " == " << b << " ? -> " <<
    (z == b ? "yes" : "no") << std::endl;
  std::cout << z << " != " << b << " ? -> " <<
    (z != b ? "yes" : "no") << std::endl;
  b = Rational(7, 9);
  std::cout << z << " == " << b << " ? -> " <<
    (z == b ? "yes" : "no") << std::endl;
  std::cout << z << " != " << b << " ? -> " <<
    (z != b ? "yes" : "no") << std::endl;
  std::cout << std::endl;
  b = Rational(1, 1);
  z = b;
  std::cout << z;
  z += 3;
  z = b;
  z += Rational(7, 3);
  z = b;
  z -= 4;
  z -= Rational(4, 5);
  z *= 9;
  z *= Rational(-4, -7);
  z /= -2;
  z /= Rational(-2, 3);
  z = Rational(12, 5);
  b = Rational(60, 54);
  z + b;
  z - b;
  z * b;
  z / b;
  z + 2;
  z - 8;
  z * 12;
  z / 36;
  try {
    std::cout << z / 0;
  }
  catch (std::invalid_argument) {
    std::cout << "Division by zero is catched" << std::endl;
  }
  try {
    std::cout << Rational(0,0);
  }
  catch (std::invalid_argument) {
    std::cout << "Division by zero is catched" << std::endl;
  }
  try {
    std::cout << z / Rational(0, 7) << std::endl;
  }
  catch (std::invalid_argument) {
    std::cout << "Division by zero is catched" << std::endl;
  }
  std::cout << std::endl;
  testParse("1/2");
  testParse("89/234");
  testParse("0/7");
  testParse("8\2");
  testParse("100/0");
}
