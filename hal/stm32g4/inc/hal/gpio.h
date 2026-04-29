#pragma once
#include "hal/core/gpio.h"
#include "hal/gen/gpio.h"
#include "stm32g4xx.h"
#include <concepts>
#include <cstdint>

namespace hal::gpio {
    template <PortTrait Port, uint8_t Idx>
    struct Pin {
        static_assert(Port::isPinValid(Idx), "The selected pin is not supported on this mcu.");

        template <PinConfigTrait Config>
        static inline void apply() {
            GPIO_TypeDef *reg = Port::reg();

            reg->MODER = (reg->MODER & ~(3 << (Idx * 2))) | static_cast<uint32_t>(Config::Mode) << (Idx * 2);
            reg->OTYPER = (reg->OTYPER & ~(1 << (Idx))) | static_cast<uint32_t>(Config::OutputType) << (Idx);
            reg->OSPEEDR = (reg->OSPEEDR & ~(3 << (Idx * 2))) | static_cast<uint32_t>(Config::Speed) << (Idx * 2);
            reg->PUPDR = (reg->PUPDR & ~(3 << (Idx * 2))) | static_cast<uint32_t>(Config::Pull) << (Idx * 2);
        }

        static inline void set() {
            GPIO_TypeDef *reg = Port::reg();

            reg->BSRR = 1 << (Idx);
        }

        static inline void reset() {
            GPIO_TypeDef *reg = Port::reg();

            reg->BSRR = 1 << (Idx + 16);
        }

        static inline bool read() {
            GPIO_TypeDef *reg = Port::reg();

            return reg->IDR & (1 << (Idx));
        }
    };
}