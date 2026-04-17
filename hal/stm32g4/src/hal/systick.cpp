#include "hal/systick.h"
#include "stm32g4xx.h"

static volatile uint64_t globalTime_ms = 0;

extern "C" void SysTick_Handler() {
    globalTime_ms = globalTime_ms + 1;
}

namespace hal::systick {

    void init(uint32_t freq) {
        SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

        uint32_t loadVal = freq / 1000 / 8;

        if(loadVal == 0) {
            loadVal = freq / 1000;
            SysTick->CTRL |= 1 << SysTick_CTRL_CLKSOURCE_Pos;
        }else{
            SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;
        }

        SysTick->CTRL |= 1 << SysTick_CTRL_TICKINT_Pos;
        SysTick->LOAD = loadVal;
        SysTick->VAL = 0;

        NVIC_SetPriority(SysTick_IRQn, 0);
        NVIC_EnableIRQ(SysTick_IRQn);

        SysTick->CTRL |= 1 << SysTick_CTRL_ENABLE_Pos;
    }

    void delay_ms(uint32_t ms) {
        uint64_t time = globalTime_ms;

        while (globalTime_ms - time < ms) {
        }
    }

    uint64_t sys_now() {
        return globalTime_ms;
    }
}