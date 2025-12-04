#ifndef GPIO_H
#define GPIO_H

#include <string>

class GPIO {
private:
  int pin;

public:
  GPIO();
  ~GPIO();

  void GPIO_SetDirection(int pin, std::string direction);
  void GPIO_SetValue(int pin, std::string value);
  void GPIO_ReadValue(int pin, int *value);
};

#endif
