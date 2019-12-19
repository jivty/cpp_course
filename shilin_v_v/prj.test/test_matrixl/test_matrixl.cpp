#include "matrixl.h"
#include <iostream>

int main() {
  MatrixL test;
  MatrixL test1(4, 3);
  MatrixL test11(test1);
  std::cout << test1.at(3,2);
  return 0;
}
