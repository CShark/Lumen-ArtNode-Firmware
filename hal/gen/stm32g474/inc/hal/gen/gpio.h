// Auto generated file. Do not edit.
#pragma once
#include "stm32g474xx.h"
#include <cstdint>

namespace hal::gpio {
    namespace internal {
        struct PortA {
            static inline GPIO_TypeDef *reg() { return GPIOA; }
            static constexpr bool isPinValid(uint8_t idx) {
                switch (idx) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    return true;
                default:
                    return false;
                }
            }
        };

        struct PortB {
            static inline GPIO_TypeDef *reg() { return GPIOB; }
            static constexpr bool isPinValid(uint8_t idx) {
                switch (idx) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    return true;
                default:
                    return false;
                }
            }
        };

        struct PortC {
            static inline GPIO_TypeDef *reg() { return GPIOC; }
            static constexpr bool isPinValid(uint8_t idx) {
                switch (idx) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    return true;
                default:
                    return false;
                }
            }
        };

        struct PortD {
            static inline GPIO_TypeDef *reg() { return GPIOD; }
            static constexpr bool isPinValid(uint8_t idx) {
                switch (idx) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    return true;
                default:
                    return false;
                }
            }
        };

        struct PortE {
            static inline GPIO_TypeDef *reg() { return GPIOE; }
            static constexpr bool isPinValid(uint8_t idx) {
                switch (idx) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    return true;
                default:
                    return false;
                }
            }
        };

        struct PortF {
            static inline GPIO_TypeDef *reg() { return GPIOF; }
            static constexpr bool isPinValid(uint8_t idx) {
                switch (idx) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    return true;
                default:
                    return false;
                }
            }
        };

        struct PortG {
            static inline GPIO_TypeDef *reg() { return GPIOG; }
            static constexpr bool isPinValid(uint8_t idx) {
                switch (idx) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                    return true;
                default:
                    return false;
                }
            }
        };

     }

    template <typename T>
    concept PortTrait = requires(uint8_t idx) {
        { T::isPinValid(idx) } -> std::convertible_to<bool>;
        { T::reg() } -> std::convertible_to<GPIO_TypeDef *>;
    };

    template <PortTrait Port, uint8_t Idx>
    struct Pin;

    using PA0 = Pin<internal::PortA, 0>;
    using PA1 = Pin<internal::PortA, 1>;
    using PA2 = Pin<internal::PortA, 2>;
    using PA3 = Pin<internal::PortA, 3>;
    using PA4 = Pin<internal::PortA, 4>;
    using PA5 = Pin<internal::PortA, 5>;
    using PA6 = Pin<internal::PortA, 6>;
    using PA7 = Pin<internal::PortA, 7>;
    using PA8 = Pin<internal::PortA, 8>;
    using PA9 = Pin<internal::PortA, 9>;
    using PA10 = Pin<internal::PortA, 10>;
    using PA11 = Pin<internal::PortA, 11>;
    using PA12 = Pin<internal::PortA, 12>;
    using PA13 = Pin<internal::PortA, 13>;
    using PA14 = Pin<internal::PortA, 14>;
    using PA15 = Pin<internal::PortA, 15>;
    using PB0 = Pin<internal::PortB, 0>;
    using PB1 = Pin<internal::PortB, 1>;
    using PB2 = Pin<internal::PortB, 2>;
    using PB3 = Pin<internal::PortB, 3>;
    using PB4 = Pin<internal::PortB, 4>;
    using PB5 = Pin<internal::PortB, 5>;
    using PB6 = Pin<internal::PortB, 6>;
    using PB7 = Pin<internal::PortB, 7>;
    using PB8 = Pin<internal::PortB, 8>;
    using PB9 = Pin<internal::PortB, 9>;
    using PB10 = Pin<internal::PortB, 10>;
    using PB11 = Pin<internal::PortB, 11>;
    using PB12 = Pin<internal::PortB, 12>;
    using PB13 = Pin<internal::PortB, 13>;
    using PB14 = Pin<internal::PortB, 14>;
    using PB15 = Pin<internal::PortB, 15>;
    using PC0 = Pin<internal::PortC, 0>;
    using PC1 = Pin<internal::PortC, 1>;
    using PC2 = Pin<internal::PortC, 2>;
    using PC3 = Pin<internal::PortC, 3>;
    using PC4 = Pin<internal::PortC, 4>;
    using PC5 = Pin<internal::PortC, 5>;
    using PC6 = Pin<internal::PortC, 6>;
    using PC7 = Pin<internal::PortC, 7>;
    using PC8 = Pin<internal::PortC, 8>;
    using PC9 = Pin<internal::PortC, 9>;
    using PC10 = Pin<internal::PortC, 10>;
    using PC11 = Pin<internal::PortC, 11>;
    using PC12 = Pin<internal::PortC, 12>;
    using PC13 = Pin<internal::PortC, 13>;
    using PC14 = Pin<internal::PortC, 14>;
    using PC15 = Pin<internal::PortC, 15>;
    using PD0 = Pin<internal::PortD, 0>;
    using PD1 = Pin<internal::PortD, 1>;
    using PD2 = Pin<internal::PortD, 2>;
    using PD3 = Pin<internal::PortD, 3>;
    using PD4 = Pin<internal::PortD, 4>;
    using PD5 = Pin<internal::PortD, 5>;
    using PD6 = Pin<internal::PortD, 6>;
    using PD7 = Pin<internal::PortD, 7>;
    using PD8 = Pin<internal::PortD, 8>;
    using PD9 = Pin<internal::PortD, 9>;
    using PD10 = Pin<internal::PortD, 10>;
    using PD11 = Pin<internal::PortD, 11>;
    using PD12 = Pin<internal::PortD, 12>;
    using PD13 = Pin<internal::PortD, 13>;
    using PD14 = Pin<internal::PortD, 14>;
    using PD15 = Pin<internal::PortD, 15>;
    using PE0 = Pin<internal::PortE, 0>;
    using PE1 = Pin<internal::PortE, 1>;
    using PE2 = Pin<internal::PortE, 2>;
    using PE3 = Pin<internal::PortE, 3>;
    using PE4 = Pin<internal::PortE, 4>;
    using PE5 = Pin<internal::PortE, 5>;
    using PE6 = Pin<internal::PortE, 6>;
    using PE7 = Pin<internal::PortE, 7>;
    using PE8 = Pin<internal::PortE, 8>;
    using PE9 = Pin<internal::PortE, 9>;
    using PE10 = Pin<internal::PortE, 10>;
    using PE11 = Pin<internal::PortE, 11>;
    using PE12 = Pin<internal::PortE, 12>;
    using PE13 = Pin<internal::PortE, 13>;
    using PE14 = Pin<internal::PortE, 14>;
    using PE15 = Pin<internal::PortE, 15>;
    using PF0 = Pin<internal::PortF, 0>;
    using PF1 = Pin<internal::PortF, 1>;
    using PF2 = Pin<internal::PortF, 2>;
    using PF3 = Pin<internal::PortF, 3>;
    using PF4 = Pin<internal::PortF, 4>;
    using PF5 = Pin<internal::PortF, 5>;
    using PF6 = Pin<internal::PortF, 6>;
    using PF7 = Pin<internal::PortF, 7>;
    using PF8 = Pin<internal::PortF, 8>;
    using PF9 = Pin<internal::PortF, 9>;
    using PF10 = Pin<internal::PortF, 10>;
    using PF11 = Pin<internal::PortF, 11>;
    using PF12 = Pin<internal::PortF, 12>;
    using PF13 = Pin<internal::PortF, 13>;
    using PF14 = Pin<internal::PortF, 14>;
    using PF15 = Pin<internal::PortF, 15>;
    using PG0 = Pin<internal::PortG, 0>;
    using PG1 = Pin<internal::PortG, 1>;
    using PG2 = Pin<internal::PortG, 2>;
    using PG3 = Pin<internal::PortG, 3>;
    using PG4 = Pin<internal::PortG, 4>;
    using PG5 = Pin<internal::PortG, 5>;
    using PG6 = Pin<internal::PortG, 6>;
    using PG7 = Pin<internal::PortG, 7>;
    using PG8 = Pin<internal::PortG, 8>;
    using PG9 = Pin<internal::PortG, 9>;
    using PG10 = Pin<internal::PortG, 10>;
}