#include <memory>
#include "Terminal.hpp"
#include "sevenSegmentOutput.hpp"


int main() {
    std::unique_ptr<oStream> stream;

    stream = std::make_unique<sevenSegmentOutput>();

    // initialize GPIOs
    auto* seg = dynamic_cast<sevenSegmentOutput*>(stream.get());
    if (seg) {
        seg->initSeg();
    }

    iStream* input = dynamic_cast<iStream*>(stream.get());
    if (!input) {
        return 1;
    }

    int digit = input->readDigit();
    if (digit == -1) {
        return 1;
    }

    stream->writeDigit(digit);

    return 0;
}
