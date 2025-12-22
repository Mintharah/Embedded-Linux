#include "GPIO.hpp"
#include <fcntl.h> // For open flags like O_WRONLY, O_CREAT, O_TRUNC
#include <iostream>
#include <unistd.h> // For write(), close()

// Implement constructor
GPIO::GPIO() { pin = -1; }

// Implement destructor
GPIO::~GPIO() {
  if (pin >= 0) {
    int fd_unexport = open("/sys/class/gpio/unexport", O_WRONLY);
    if (fd_unexport >= 0) {
      std::string pin_str = std::to_string(pin + 512);
      write(fd_unexport, pin_str.c_str(), pin_str.size());
      close(fd_unexport);
    }
  }
}

void GPIO::GPIO_SetDirection(int pin, std::string direction) {
  std::string pin_str = std::to_string(pin + 512);
  std::string full_direction_path =
      "/sys/class/gpio/gpio" + pin_str + "/direction";

  int fd_export = open("/sys/class/gpio/export", O_WRONLY);
  if (fd_export >= 0) {
    write(fd_export, pin_str.c_str(), pin_str.size());
    std::cout << "Pin number wrote to export!! (:" << std::endl;
  } else {
    perror("Couldn't open export :(\n");
  }

  int fd_direction = open(full_direction_path.c_str(), O_WRONLY);
  if (fd_direction >= 0) {
    write(fd_direction, direction.c_str(), direction.size());
    close(fd_direction);
    fd_direction = -1;
    std::cout << "Wrote direction!! (:" << std::endl;
  } else {
    perror("Couldn't open direction :(\n");
  }
  close(fd_export);
  fd_export = -1;
}

void GPIO::GPIO_SetValue(int pin, std::string value) {

  std::string pin_str = std::to_string(pin + 512);
  std::string full_value_path = "/sys/class/gpio/gpio" + pin_str + "/value";

  int fd_export = open("/sys/class/gpio/export", O_WRONLY);
  if (fd_export >= 0) {
    write(fd_export, pin_str.c_str(), pin_str.size());
    std::cout << "Pin number wrote to export!! (:" << std::endl;
  } else {
    perror("Couldn't open export :(\n");
  }

  int fd_value = open(full_value_path.c_str(), O_WRONLY);
  if (fd_value >= 0) {
    write(fd_value, value.c_str(), value.size());
    close(fd_value);
    fd_value = -1;
    std::cout << "Wrote value!! (:" << std::endl;
  } else {
    perror("Couldn't open value:(\n");
  }

  close(fd_export);
  fd_export = -1;
}

void GPIO::GPIO_ReadValue(int pin, int *value) {
  std::string pin_str = std::to_string(pin + 512);
  std::string full_value_path = "/sys/class/gpio/gpio" + pin_str + "/value";

  int fd_export = open("/sys/class/gpio/export", O_WRONLY);
  if (fd_export >= 0) {
    write(fd_export, pin_str.c_str(), pin_str.size());
    std::cout << "Pin number wrote to export!! (:" << std::endl;
  } else {
    perror("Couldn't open export :(\n");
  }

  int fd_value = open(full_value_path.c_str(), O_RDONLY);
  if (fd_value >= 0) {
    char buff[2] = {0};
    read(fd_value, buff, 1);
    *value = buff[0] - '0';
    close(fd_value);
    fd_value = -1;
    std::cout << "Wrote value!! (:" << std::endl;
    std::cout << *value << std::endl;

  } else {
    perror("Couldn't read value:(\n");
  }
  close(fd_export);
  fd_export = -1;
}
