#include "ortosegm.h"
#include <iostream>

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