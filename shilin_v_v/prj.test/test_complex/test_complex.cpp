#include "complex.h"
#include <iostream>
#include <sstream>

bool testParse(const std::string& str) {
  std::istringstream istrm(str);
  Complex z;
  istrm >> z;
  if (istrm.good()) {
    std::cout << "Read success: " << str << " -> " << z << std::endl;
  } else {
    std::cout << "Read error: " << str << " -> " << z << std::endl;
  }
  return istrm.good();
}

int main() {
  Complex z, b;
  std::cout << "z = " << z << std::endl;
  z = 3.1;
  std::cout << "z = 3.1 : z -> " << z << std::endl;
  z = Complex(3, -8);
  std::cout << "z = {3,-8} : z -> " << z << std::endl;
  std::cout << " -z : z -> " << -z << std::endl;
  std::cout << std::endl;
  b = Complex(z);
  std::cout << "b = Complex(z) : b -> " << b << std::endl;
  std::cout << z << " == " << b << " ? -> " <<
    (z == b ? "yes" : "no") << std::endl;
  std::cout << z << " != " << b << " ? -> " <<
    (z != b ? "yes" : "no") << std::endl;
  b = Complex(1, 2);
  std::cout << z << " == " << b << " ? -> " <<
    (z == b ? "yes" : "no") << std::endl;
  std::cout << z << " != " << b << " ? -> " <<
    (z != b ? "yes" : "no") << std::endl;
  std::cout << std::endl;
  z = Complex(1, 1);
  std::cout << z;
  z += Complex(8.1);
  std::cout << " += {8.1} -> " << z << std::endl;
  z = Complex(2, 2);
  std::cout << z;
  z += 2.71;
  std::cout << " += 2.71 -> " << z << std::endl;
  z = Complex(-3, 3);
  std::cout << z;
  z -= Complex(5, 3);
  std::cout << " -= {5,3} -> " << z << std::endl;
  z = Complex(4, -4);
  std::cout << z;
  z -= 2.2;
  std::cout << " -= 2.2 -> " << z << std::endl;
  z = Complex(5, 5);
  std::cout << z;
  z *= Complex(3, -4);
  std::cout << " *= {3,4} -> " << z << std::endl;
  z = Complex(-6, 6);
  std::cout << z;
  z *= 7.9;
  std::cout << " *= 7.9 -> " << z << std::endl;
  z = Complex(4, 4);
  std::cout << z;
  z /= Complex(2, 2);
  std::cout << " /= {2,2} -> " << z << std::endl;
  z = Complex(5, 5);
  std::cout << z;
  z /= 2.5;
  std::cout << " /= 2.5 -> " << z << std::endl;
  std::cout << std::endl;
  z = Complex(3, -2); b = Complex(-8, 4);
  std::cout << z << " + " << b << " = " << z + b << std::endl;
  std::cout << z << " - " << b << " = " << z - b << std::endl;
  std::cout << z << " * " << b << " = " << z * b << std::endl;
  std::cout << z << " / " << b << " = " << z / b << std::endl;
  std::cout << std::endl;
  std::cout << z << " + 3.2 = " << z + 3.2 << std::endl;
  std::cout << "4.2 + " << z << " = " << 4.2 + z << std::endl;
  std::cout << z << " - 4.7 = " << z - 4.7 << std::endl;
  std::cout << "7.8 - " << z << " = " << 7.8 - z << std::endl;
  std::cout << z << " * 0.9 = " << z * 0.9 << std::endl;
  std::cout << "1.2 * " << z << " = " << 1.2 * z << std::endl;
  std::cout << z << " / 5 = " << z / 5 << std::endl;
  std::cout << "10 / " << z << " = " << 10 / z << std::endl;
  std::cout << std::endl;
  std::cout << "z / 0 = ";
  try {
    std::cout << z / 0;
  }
  catch(std::invalid_argument) {
    std::cout << "Division by zero is cathed" << std::endl;
  }
  std::cout << "z / Complex(0, 0) = ";
  try {
    std::cout << z / Complex(0, 0);
  }
  catch(std::invalid_argument) {
    std::cout << "Division by zero is cathed" << std::endl;
  }
  std::cout << std::endl;
  testParse("{8.9,9}");
  testParse("(8.9,9)");
  testParse("{8.9, 9}");
  testParse("{8.9,9");
  return 0;
}
