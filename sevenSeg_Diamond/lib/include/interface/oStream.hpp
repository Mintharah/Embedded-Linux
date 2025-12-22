#ifndef OSTREAM_HPP
#define OSTREAM_HPP

#include "private/Stream_Base.hpp"

class oStream : virtual public Stream {
public:
  virtual ~oStream() = default;
  virtual void writeDigit(int digit) = 0;
};

#endif