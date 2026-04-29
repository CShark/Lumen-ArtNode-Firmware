// Auto generated file. Do not edit.
#pragma once
#include "stm32g474xx.h"
#include "hal/gpio.h"
#include <cstdint>

#define MAP_UART_AF(uart, pin, role, af) \
    template<>\
    struct internal::UartAfMapping<uart, pin, role> {\
        static constexpr int afValue = af;\
    }

namespace hal::uart {
    namespace internal {
        struct TagRx {};
        struct TagTx {};
        struct TagCts {};
        struct TagRts {};
        struct TagNss {};
        struct TagDe {};
        struct TagCk {};

        template<typename Uart, typename Pin, typename Role>
        struct UartAfMapping {
            static constexpr int afValue = -1;
        };
    }

    struct Uart4 {
        static constexpr uintptr_t reg = UART4_BASE;
        static constexpr uint8_t irq = UART4_IRQn;
        static constexpr char name[] = "UART4";

        static void rcc_enable() {
            RCC->APB1ENR1 |= RCC_APB1ENR1_UART4EN;
            (void)RCC->APB1ENR1;
        }

        static void rcc_disable() {
            RCC->APB1ENR1 &= ~RCC_APB1ENR1_UART4EN;
        }

        static void rcc_reset() {
            RCC->APB1RSTR1 |= RCC_APB1RSTR1_UART4RST;
            RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_UART4RST;
        }
    };
    MAP_UART_AF(Uart4, gpio::PA15, internal::TagDe, 8);
    MAP_UART_AF(Uart4, gpio::PA15, internal::TagRts, 8);
    MAP_UART_AF(Uart4, gpio::PB7, internal::TagCts, 14);
    MAP_UART_AF(Uart4, gpio::PC10, internal::TagTx, 5);
    MAP_UART_AF(Uart4, gpio::PC11, internal::TagRx, 5);

    struct Uart5 {
        static constexpr uintptr_t reg = UART5_BASE;
        static constexpr uint8_t irq = UART5_IRQn;
        static constexpr char name[] = "UART5";

        static void rcc_enable() {
            RCC->APB1ENR1 |= RCC_APB1ENR1_UART5EN;
            (void)RCC->APB1ENR1;
        }

        static void rcc_disable() {
            RCC->APB1ENR1 &= ~RCC_APB1ENR1_UART5EN;
        }

        static void rcc_reset() {
            RCC->APB1RSTR1 |= RCC_APB1RSTR1_UART5RST;
            RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_UART5RST;
        }
    };
    MAP_UART_AF(Uart5, gpio::PB4, internal::TagDe, 8);
    MAP_UART_AF(Uart5, gpio::PB4, internal::TagRts, 8);
    MAP_UART_AF(Uart5, gpio::PB5, internal::TagCts, 14);
    MAP_UART_AF(Uart5, gpio::PC12, internal::TagTx, 5);
    MAP_UART_AF(Uart5, gpio::PD2, internal::TagRx, 5);

    struct Usart1 {
        static constexpr uintptr_t reg = USART1_BASE;
        static constexpr uint8_t irq = USART1_IRQn;
        static constexpr char name[] = "USART1";

        static void rcc_enable() {
            RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
            (void)RCC->APB2ENR;
        }

        static void rcc_disable() {
            RCC->APB2ENR &= ~RCC_APB2ENR_USART1EN;
        }

        static void rcc_reset() {
            RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST;
            RCC->APB2RSTR &= ~RCC_APB2RSTR_USART1RST;
        }
    };
    MAP_UART_AF(Usart1, gpio::PA10, internal::TagRx, 7);
    MAP_UART_AF(Usart1, gpio::PA11, internal::TagCts, 7);
    MAP_UART_AF(Usart1, gpio::PA11, internal::TagNss, 7);
    MAP_UART_AF(Usart1, gpio::PA12, internal::TagDe, 7);
    MAP_UART_AF(Usart1, gpio::PA12, internal::TagRts, 7);
    MAP_UART_AF(Usart1, gpio::PA8, internal::TagCk, 7);
    MAP_UART_AF(Usart1, gpio::PA9, internal::TagTx, 7);
    MAP_UART_AF(Usart1, gpio::PB6, internal::TagTx, 7);
    MAP_UART_AF(Usart1, gpio::PB7, internal::TagRx, 7);
    MAP_UART_AF(Usart1, gpio::PC4, internal::TagTx, 7);
    MAP_UART_AF(Usart1, gpio::PC5, internal::TagRx, 7);
    MAP_UART_AF(Usart1, gpio::PE0, internal::TagTx, 7);
    MAP_UART_AF(Usart1, gpio::PE1, internal::TagRx, 7);
    MAP_UART_AF(Usart1, gpio::PG9, internal::TagTx, 7);

    struct Usart2 {
        static constexpr uintptr_t reg = USART2_BASE;
        static constexpr uint8_t irq = USART2_IRQn;
        static constexpr char name[] = "USART2";

        static void rcc_enable() {
            RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;
            (void)RCC->APB1ENR1;
        }

        static void rcc_disable() {
            RCC->APB1ENR1 &= ~RCC_APB1ENR1_USART2EN;
        }

        static void rcc_reset() {
            RCC->APB1RSTR1 |= RCC_APB1RSTR1_USART2RST;
            RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_USART2RST;
        }
    };
    MAP_UART_AF(Usart2, gpio::PA0, internal::TagCts, 7);
    MAP_UART_AF(Usart2, gpio::PA0, internal::TagNss, 7);
    MAP_UART_AF(Usart2, gpio::PA1, internal::TagDe, 7);
    MAP_UART_AF(Usart2, gpio::PA1, internal::TagRts, 7);
    MAP_UART_AF(Usart2, gpio::PA14, internal::TagTx, 7);
    MAP_UART_AF(Usart2, gpio::PA15, internal::TagRx, 7);
    MAP_UART_AF(Usart2, gpio::PA2, internal::TagTx, 7);
    MAP_UART_AF(Usart2, gpio::PA3, internal::TagRx, 7);
    MAP_UART_AF(Usart2, gpio::PA4, internal::TagCk, 7);
    MAP_UART_AF(Usart2, gpio::PB3, internal::TagTx, 7);
    MAP_UART_AF(Usart2, gpio::PB4, internal::TagRx, 7);
    MAP_UART_AF(Usart2, gpio::PB5, internal::TagCk, 7);
    MAP_UART_AF(Usart2, gpio::PD3, internal::TagCts, 7);
    MAP_UART_AF(Usart2, gpio::PD3, internal::TagNss, 7);
    MAP_UART_AF(Usart2, gpio::PD4, internal::TagDe, 7);
    MAP_UART_AF(Usart2, gpio::PD4, internal::TagRts, 7);
    MAP_UART_AF(Usart2, gpio::PD5, internal::TagTx, 7);
    MAP_UART_AF(Usart2, gpio::PD6, internal::TagRx, 7);
    MAP_UART_AF(Usart2, gpio::PD7, internal::TagCk, 7);

    struct Usart3 {
        static constexpr uintptr_t reg = USART3_BASE;
        static constexpr uint8_t irq = USART3_IRQn;
        static constexpr char name[] = "USART3";

        static void rcc_enable() {
            RCC->APB1ENR1 |= RCC_APB1ENR1_USART3EN;
            (void)RCC->APB1ENR1;
        }

        static void rcc_disable() {
            RCC->APB1ENR1 &= ~RCC_APB1ENR1_USART3EN;
        }

        static void rcc_reset() {
            RCC->APB1RSTR1 |= RCC_APB1RSTR1_USART3RST;
            RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_USART3RST;
        }
    };
    MAP_UART_AF(Usart3, gpio::PA13, internal::TagCts, 7);
    MAP_UART_AF(Usart3, gpio::PA13, internal::TagNss, 7);
    MAP_UART_AF(Usart3, gpio::PB10, internal::TagTx, 7);
    MAP_UART_AF(Usart3, gpio::PB11, internal::TagRx, 7);
    MAP_UART_AF(Usart3, gpio::PB12, internal::TagCk, 7);
    MAP_UART_AF(Usart3, gpio::PB13, internal::TagCts, 7);
    MAP_UART_AF(Usart3, gpio::PB13, internal::TagNss, 7);
    MAP_UART_AF(Usart3, gpio::PB14, internal::TagDe, 7);
    MAP_UART_AF(Usart3, gpio::PB14, internal::TagRts, 7);
    MAP_UART_AF(Usart3, gpio::PB8, internal::TagRx, 7);
    MAP_UART_AF(Usart3, gpio::PB9, internal::TagTx, 7);
    MAP_UART_AF(Usart3, gpio::PC10, internal::TagTx, 7);
    MAP_UART_AF(Usart3, gpio::PC11, internal::TagRx, 7);
    MAP_UART_AF(Usart3, gpio::PC12, internal::TagCk, 7);
    MAP_UART_AF(Usart3, gpio::PD10, internal::TagCk, 7);
    MAP_UART_AF(Usart3, gpio::PD11, internal::TagCts, 7);
    MAP_UART_AF(Usart3, gpio::PD11, internal::TagNss, 7);
    MAP_UART_AF(Usart3, gpio::PD12, internal::TagDe, 7);
    MAP_UART_AF(Usart3, gpio::PD12, internal::TagRts, 7);
    MAP_UART_AF(Usart3, gpio::PD8, internal::TagTx, 7);
    MAP_UART_AF(Usart3, gpio::PD9, internal::TagRx, 7);
    MAP_UART_AF(Usart3, gpio::PE15, internal::TagRx, 7);
    MAP_UART_AF(Usart3, gpio::PF6, internal::TagRts, 7);

}

#undef MAP_UART_AF