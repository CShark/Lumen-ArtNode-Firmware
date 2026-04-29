#pragma once
#include "hal/core/uart.h"
#include "hal/gen/uart.h"
#include "hal/gpio.h"
#include "logger.h"
#include <concepts>
#include <string_view>

namespace hal::uart {
    template <typename T>
    concept UartTrait = requires {
        { T::reg } -> std::convertible_to<uintptr_t>;
        { T::irq } -> std::convertible_to<uint8_t>;
        { T::name } -> std::convertible_to<std::string_view>;
        { T::rcc_enable() } -> std::same_as<void>;
        { T::rcc_disable() } -> std::same_as<void>;
        { T::rcc_reset() } -> std::same_as<void>;
    };

    template <UartTrait Uart, typename TX, typename RX>
    struct Usart {
    private:
        static constexpr uint32_t txAf = internal::UartAfMapping<Uart, TX, internal::TagTx>::afValue;
        static constexpr uint32_t rxAf = internal::UartAfMapping<Uart, RX, internal::TagRx>::afValue;

        static_assert(txAf != -1, "TX pin is not valid for this USART instance");
        static_assert(rxAf != -1, "RX pin is not valid for this USART instance");

    public:
        Usart(Baudrate baudrate) {
            Uart::rcc_enable();
            Uart::rcc_reset();

            TX::template apply<gpio::PinConfig<gpio::PinMode::Alternate, gpio::PinPull::None, gpio::PinOutputType::PushPull, gpio::PinSpeed::Medium, txAf>>();
            RX::template apply<gpio::PinConfig<gpio::PinMode::Alternate, gpio::PinPull::None, gpio::PinOutputType::PushPull, gpio::PinSpeed::Medium, rxAf>>();

            setBaudrate(baudrate);
        }

        ~Usart() {
            Uart::rcc_reset();
            Uart::rcc_disable();
        }

        void setBaudrate(Baudrate baudrate) {
            auto regs = reinterpret_cast<USART_TypeDef *>(Uart::reg);

            regs->CR1 &= ~(USART_CR1_TE | USART_CR1_RE | USART_CR1_UE);

            regs->BRR = baudrate.BRR;
            if (baudrate.OVER8) {
                regs->CR1 |= USART_CR1_OVER8;
            } else {
                regs->CR1 &= ~USART_CR1_OVER8;
            }

            regs->CR1 |= (USART_CR1_TE | USART_CR1_RE | USART_CR1_UE);

            char buf[128]{0};
            snprintf(buf, sizeof(buf), "%s configured to %.4f KHz", Uart::name, baudrate.realFreq / 1000.0);
            logger::debug(buf);
        }

        void writeBlocking(uint8_t data) {
            auto regs = reinterpret_cast<USART_TypeDef *>(Uart::reg);
            while (!(regs->ISR & USART_ISR_TXE)) {
            }
            regs->TDR = data;
        }

        uint8_t readBlocking() {
            auto regs = reinterpret_cast<USART_TypeDef *>(Uart::reg);
            while (!(regs->ISR & USART_ISR_RXNE)) {
            }
            return static_cast<uint8_t>(regs->TDR);
        }
    };
}