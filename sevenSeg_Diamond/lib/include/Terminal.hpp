#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include "interface/iStream.hpp"
#include "interface/oStream.hpp"

class Terminal : public oStream, public iStream {
public:
  void writeDigit(int digit) override;
};

#endif