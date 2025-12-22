#include "Terminal.hpp"
#include <iostream>

void Terminal::writeDigit(int digit) {
  if ((digit > 0) && (digit < 9)) {
    std::cout << "The digit written on the seven segment is: " << digit
              << std::endl;
  } else {
    std::cout << "invalid input:(\n";
  }
}