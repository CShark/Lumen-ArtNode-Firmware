#include "hal/core/rcc.h"
#include "system_stm32g4xx.h"

namespace hal::rcc {
    uint32_t getSystemCoreClock() {
        return SystemCoreClock;
    }
}