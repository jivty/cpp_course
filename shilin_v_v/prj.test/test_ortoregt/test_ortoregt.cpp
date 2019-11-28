#include "ortoregt.h"
#include <iostream>

int main() {
  OrtoRegt test;

  OrtoRegt test2(12, 0, 1, 2);
  OrtoRegt test3(1, 1, 2, 2);
  OrtoRegt test4(test2);
  std::cout << test.high() << " " << test.width() << std::endl;
  std::cout << test2.high() << " " << test2.width() << std::endl;
  std::cout << test3.high() << " " << test3.width() << std::endl;
  test3.move(1, 1);
  if (test2.contain(1, 2)) std::cout << "yes";

  return 0;
}