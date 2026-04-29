#pragma once
#include <concepts>
#include <cstdint>

namespace hal::rcc {
    uint32_t getSystemCoreClock();

    template <typename T>
    concept ClockConfigTrait = requires {
        { T::sysclk } -> std::convertible_to<uint32_t>;
        { T::pclk } -> std::convertible_to<uint32_t>;
    };
}