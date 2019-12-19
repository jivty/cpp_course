#include <dynarrayt/dynarrayt.h>
#include <iostream>
#include <vector>

int main() {
  DynArrayT<char> arr;
  std::cout << arr.size() << " " << arr.capacity();
  arr.resize(5);
  for (int i = 0; i < 5; ++i) {
    arr[i] = 'a';
  }
  std::cout << std::endl;
  DynArrayT<char> arr2(7);
  for (int i = 0; i < arr2.size(); i++) std::cout << arr2[i] << std::endl;
  arr2 = arr;
  std::cout << std::endl;
  for (int i = 0; i < arr2.size(); i++) std::cout << arr2[i];
  arr2.resize(7);
  std::cout << std::endl;
  for (int i = 0; i < arr2.size(); i++) std::cout << arr2[i];
  arr2 = arr;
  std::cout<< std::endl;
  for (int i = 0; i < arr2.size(); i++) std::cout << arr2[i];
  return 0;
}
