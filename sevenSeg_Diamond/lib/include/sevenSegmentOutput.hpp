#ifndef SEVENSEGMENTOUTPUT_HPP
#define SEVENSEGMENTOUTPUT_HPP

#include <cstdint>
#include "private/GPIO.hpp"
#include "interface/iStream.hpp"
#include "interface/oStream.hpp"


class sevenSegmentOutput : public iStream, public oStream {
private:
  GPIO gpio;
  uint8_t pins[7] = {17, 27, 22, 23, 24, 25, 26};
  uint8_t segLUT[10] = {
      0x40, // 0
      0x79, // 1
      0x24, // 2
      0x30, // 3
      0x19, // 4
      0x12, // 5
      0x02, // 6
      0x78, // 7
      0x00, // 8
      0x10  // 9
  };

public:
  void initSeg(void);
  void writeDigit(int digit) override;
};

#endif