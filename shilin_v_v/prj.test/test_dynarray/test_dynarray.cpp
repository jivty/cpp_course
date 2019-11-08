#include "dynarray.h"
#include <iostream>
#include <vector>

int main() {
  DynArray arr;
  std::cout << arr.size() << " " << arr.capacity();
  arr.resize(5);
  for (int i = 0; i < 5; ++i) { 
    arr[i] = i + 1; 
  }
  std::cout << std::endl;
  DynArray arr2(7);
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
