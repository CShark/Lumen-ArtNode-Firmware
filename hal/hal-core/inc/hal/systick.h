#pragma once
#include <cstdint>

namespace hal::systick {
    void init();
    void delay_ms(uint32_t ms);
    uint64_t sys_now();
}