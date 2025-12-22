#include "interface/iStream.hpp"
#include <iostream>

int iStream::readDigit() {
  int digit;

  std::cout << "Please enter a digit between 0 and 9: ";
  std::cin >> digit;

  if ((digit < 0) || (digit > 9) || (std::cin.fail())) {
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    return -1; // invalid input
  }
  return digit;
}