#include "rational.h"
#include <iostream>
#include <sstream>

bool testParse(const std::string& str) {
  std::istringstream istrm(str);
  Rational z;
  istrm >> z;
  if (istrm.good()) {
    std::cout << "Read succes: " << str << " -> " << z << std::endl;
  } else {
    std::cout << "Read error: " << str << " -> " << z << std::endl;
  }
  return istrm.good();
}

int main() {
  Rational z, b;
  std::cout << "z = " << z << std::endl;
  z = 4;
  std::cout << "z = 4 : z -> " << z << std::endl;
  z = Rational(-4, -2);
  std::cout << "z = (-4)/(-2) : z -> " << z << std::endl;
  b = Rational(z);
  std::cout << "b = Rational(z) : b -> " << b << std::endl;
  std::cout << std::endl;
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
  z = Rational(3, 4);
  std::cout << z;
  z += Rational(7, 3);
  std::cout << " += 7/3 -> " << z << std::endl;
  std::cout << z;
  z += 3;
  std::cout << " += 3 -> " << z << std::endl;
  std::cout << z;
  z -= 4;
  std::cout << " -= 4 -> " << z << std::endl;
  std::cout << z;
  z -= Rational(1, 3);
  std::cout << " -= 1/3 -> " << z << std::endl;
  std::cout << z;
  z *= -9;
  std::cout << " *= -9 -> " << z << std::endl;
  std::cout << z;
  z *= Rational(-4, -7);
  std::cout << " *= (-4)/(-7) -> " << z << std::endl;
  std::cout << z;
  z /= -2;
  std::cout << " /= -2  -> " << z << std::endl;
  std::cout << z;
  z /= Rational(-2, 3);
  std::cout << " /= -2/3 -> " << z << std::endl;
  std::cout << std::endl;
  z = Rational(-12, -5);
  b = Rational(60, 54);
  std::cout << z << " + " << b << " = " << z + b << std::endl;
  std::cout << z << " - " << b << " = " << z - b << std::endl;
  std::cout << z << " * " << b << " = " << z * b << std::endl;
  std::cout << z << " / " << b << " = " << z / b << std::endl;
  std::cout << std::endl;
  std::cout << z << " + 3 = " << z + 3 << std::endl;
  std::cout << "4 + " << z << " = " << 4 + z << std::endl;
  std::cout << z << " - 8 = " << z - 8 << std::endl;
  std::cout << "7 - " << z << " = " << 7 - z << std::endl;
  std::cout << z << " * 10 = " << z * 10 << std::endl;
  std::cout << "-3 * " << z << " = " << -3 * z << std::endl;
  std::cout << z << " / 5 = " << z / 5 << std::endl;
  std::cout << "10 / " << z << " = " << 10 / z << std::endl;
  std::cout << std::endl;
  std::cout << "z / 0 = ";
  try {
    std::cout << z / 0;
  }
  catch (std::invalid_argument) {
    std::cout << "Division by zero is catched" << std::endl;
  }
  std::cout << "z / 0/7 = ";
  try {
    std::cout << z / Rational(0, 7) << std::endl;
  }
  catch (std::invalid_argument) {
    std::cout << "Division by zero is catched" << std::endl;
  }
  std::cout << "7/0 = ";
  try {
    std::cout << Rational(7,0);
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
