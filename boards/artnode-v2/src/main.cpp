#include "hal/hal.h"
#include "logger.h"

extern "C" int main(void) {
    using pll = hal::rcc::PLLAuto<hal::rcc::HSE<hal::MHz<25>>, hal::MHz<144>>;
    using rcc = hal::rcc::ClockConfig<pll, hal::rcc::PLLR<pll>>;

    rcc::init();

    auto baudrate = hal::uart::BaudrateHelper<hal::KHz<128>>::fromRcc<rcc>();

    auto uart = hal::uart::Usart<hal::uart::Usart1, hal::gpio::PB6, hal::gpio::PB7>(baudrate);

    while (true) {
    }
}