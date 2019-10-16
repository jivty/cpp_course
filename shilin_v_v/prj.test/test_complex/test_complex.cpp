#include "complex.h"
#include <iostream>
#include <sstream>
#include <string>

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
  Complex z;
  std::cout << "z = " << z << std::endl;
  z = 3.14;
  std::cout << "z = 3.14 : z -> " << z << std::endl;
  z = Complex(-43.2, -8);
  std::cout << "z = Complex(-43.2, -8) : z -> " << z << std::endl;
  std::cout << std::endl;
  std::cout << "z == Complex(-43.2, -8) ? -> " <<
    (z == Complex(-43.2, -8) ? "yes" : "no") << std::endl;
  std::cout << "z != Complex(1, 2) ? -> " <<
    (z != Complex(1, 2) ? "yes" : "no") << std::endl;
  std::cout << std::endl;
  z += Complex(8.1);
  std::cout << "z += Complex(8.1) : z -> " << z << std::endl;
  z += 2.71;
  std::cout << "z += 2.71 : z -> " << z << std::endl;
  z -= Complex(5.0, 3.2);
  std::cout << "z -= Complex(5.0, 3.2) : z -> " << z << std::endl;
  z -= 2.71;
  std::cout << "z -= 2.71 : z -> " << z << std::endl;
  z *= Complex(3.2, 4.5);
  std::cout << "z *= Complex(3.2, 4.5) : z -> " << z << std::endl;
  z *= 7.9;
  std::cout << "z *= 7.9 : z -> " << z << std::endl;
  z /= Complex(1.2, 2.3);
  std::cout << "z /= Complex(1.2, 2.3) : z -> " << z << std::endl;
  z /= 1.5;
  std::cout << "z /= 1.5 : z -> " << z << std::endl;
  z = conj(z);
  std::cout << "z = conj(z) : z -> " << z << std::endl;
  std::cout << std::endl;
  Complex b(27.32, -8.9);
  std::cout << "b = " << b << std::endl;
  std::cout << "z + b = " << z + b << std::endl;
  std::cout << "z - b = " << z - b << std::endl;
  std::cout << "z * b = " << z * b << std::endl;
  std::cout << "z / b = " << z / b << std::endl;
  std::cout << std::endl;
  std::cout << "z = " << z << std::endl;
  std::cout << "z + 3.2 = " << z + 3.2 << std::endl;
  std::cout << "4.2 + z = " << 4.2 + z << std::endl;
  std::cout << "z - 4.7 = " << z - 4.7 << std::endl;
  std::cout << "7.8 - z = " << 7.8 - z << std::endl;
  std::cout << "z * 0.9 = " << z * 0.9 << std::endl;
  std::cout << "1.2 * z = " << 1.2 * z << std::endl;
  std::cout << "z / 0.9 = " << z / 0.9 << std::endl;
  std::cout << "0.9 / z = " << 0.9 / z << std::endl;
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
  testParse("(8.9,9)");
  testParse("{8.9,9}");
  testParse("(8.9, 9)");
  testParse("(8.9,9");
  return 0;
}
