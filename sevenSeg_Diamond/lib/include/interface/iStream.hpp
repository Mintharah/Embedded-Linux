#ifndef ISTREAM_HPP
#define ISTREAM_HPP

#include "private/Stream_Base.hpp"

class iStream : virtual public Stream {
public:
  virtual ~iStream() = default;
  int readDigit();
};

#endif