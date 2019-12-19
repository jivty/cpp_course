#include <stacka/stacka.h>
#include <iostream>

int main() {
  StackA test;
  StackA testc(test);
  std::cout << test.is_empty() << std::endl;
  test.push(1);
  std::cout << test.is_empty() << std::endl;
}