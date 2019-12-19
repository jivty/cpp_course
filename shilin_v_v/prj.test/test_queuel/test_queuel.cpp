#include <queuel/queuel.h>
#include <iostream>

void clearandshow(QueueL& obj) {
  while (!obj.is_empty()) {
    std::cout << obj.top() << " ";
    obj.pop();
  }
  std::cout << std::endl;
}

int main() {
  QueueL test;
  try {
    test.top();
  } catch (std::logic_error) {
    std::cout << "top in empty queue is catched" << std::endl;
  }
  test.push(1);
  std::cout << test.top() << " ";
  test.push(2);
  clearandshow(test);
  try {
    test.top();
  }
  catch (std::logic_error) {
    std::cout << "top in empty queue is catched" << std::endl;
  }
  test.push(1);
  test.push(2);
  QueueL testcopy(test);
  std::cout << "testcopy(test) -> testcopy: ";
  clearandshow(testcopy);
  QueueL test2(test);
  test2 = testcopy;
  std::cout << "test2(test) = testcopy(empty) -> test2: ";
  clearandshow(test2);
  test2 = test;
  std::cout << "test2(empty) = test(not empty) -> test2: ";
  clearandshow(test2);
}
