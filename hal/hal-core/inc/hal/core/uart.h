#pragma once
#include "hal/core/rcc.h"
#include "hal/utils.h"
#include <concepts>

namespace hal::uart {
    struct Baudrate {
        uint16_t BRR;
        bool OVER8;
        uint32_t realFreq;
    };

    template <HzTrait Freq>
    struct BaudrateHelper {
    private:
        static constexpr Baudrate calculateRegisters(uint32_t srcFreq, uint32_t dstFreq) {
            uint32_t clock = srcFreq;
            uint32_t target = dstFreq;

            uint32_t div4 = (clock * 4) / target;
            uint32_t usart_div = 0;
            bool over8 = false;

            if ((div4 & 0b01) == 1) {
                usart_div = (div4 >> 1) + 1;
                usart_div &= 0x7FFF;
                over8 = true;
            } else if ((div4 & 0b10) == 0b10) {
                usart_div = (div4 >> 1);
                usart_div &= 0x7FFF;
                over8 = true;
            } else {
                usart_div = (div4 >> 2);
                usart_div &= 0xFFFF;
                over8 = false;
            }

            if (usart_div < 16)
                usart_div = 16;

            uint32_t finalFreq = over8 ? (clock * 2) / usart_div : clock / usart_div;

            uint16_t brr = 0;
            if (over8) {
                brr = static_cast<uint16_t>((usart_div & 0xFFF0) | ((usart_div & 0x0007)));
            } else {
                brr = static_cast<uint16_t>(usart_div);
            }

            return {brr, over8, finalFreq};
        }

    public:
        template <rcc::ClockConfigTrait Rcc>
        static consteval Baudrate fromRcc() {
            return calculateRegisters(Rcc::pclk, Freq::hz);
        }

        static Baudrate fromRuntime() {
            return calculateRegisters(rcc::getSystemCoreClock(), Freq::hz);
        };
    };
}