#include <queuea/queuea.h>
#include <iostream>

int main() {
  QueueA test;
  QueueA test1(test);
  QueueA test2;
  test2.push(1);
  test = test2;
  test2 = test1;
  std::cout << test.top() << std::endl;
  test.pop();
  try {
    test1.pop();
  } catch (std::logic_error) {
    std::cout << "pop in empty queue is catched" << std::endl;
  }
  try {
    test1.top();
  }
  catch (std::logic_error) {
    std::cout << "top in empty queue is catched" << std::endl;
  }
  return 0;
}