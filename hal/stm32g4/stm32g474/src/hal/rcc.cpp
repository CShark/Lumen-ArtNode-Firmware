#include "rcc.h"

namespace hal::rcc {
    uint32_t getSystemCoreClock() {
        return SystemCoreClock;
    }
}