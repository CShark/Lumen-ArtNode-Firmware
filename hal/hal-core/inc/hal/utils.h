#pragma once
#include <concepts>
#include <cstdint>

namespace hal {
    template <unsigned int freq>
    struct Hz {
        static constexpr uint32_t hz = freq;
    };

    template <unsigned int freq>
    struct KHz {
        static constexpr uint32_t hz = freq * 1000;
    };

    template <unsigned int freq>
    struct MHz {
        static constexpr uint32_t hz = freq * 1000 * 1000;
    };

    template <typename T>
    concept HzTrait = requires {
        { T::hz } -> std::convertible_to<uint32_t>;
    };
}