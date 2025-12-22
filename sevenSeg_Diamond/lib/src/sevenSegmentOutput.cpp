#include "sevenSegmentOutput.hpp"
#include <unistd.h>

void sevenSegmentOutput::initSeg() {
  for (int i = 0; i < 7; i++) {
    gpio.GPIO_SetDirection(pins[i], "out");
    gpio.GPIO_SetValue(pins[i], "1");
  }
}

void sevenSegmentOutput::writeDigit(int digit) {
  uint8_t pattern = segLUT[digit];
  for (int i = 0; i < 7; i++) {
    if ((pattern >> i) & 1) {
      gpio.GPIO_SetValue(pins[i], "1");
    } else {
      gpio.GPIO_SetValue(pins[i], "0");
    }
  }
}