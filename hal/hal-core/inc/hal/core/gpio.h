#pragma once
#include <concepts>
#include <cstdint>

namespace hal::gpio {
    enum class PinMode : uint32_t { Input = 0,
                                    Output = 1,
                                    Alternate = 2,
                                    Analog = 3 };
    enum class PinOutputType : uint32_t { PushPull = 0,
                                          OpenDrain = 1 };
    enum class PinSpeed : uint32_t { Low = 0,
                                     Medium = 1,
                                     High = 2,
                                     VeryHigh = 3 };
    enum class PinPull : uint32_t { None = 0,
                                    PullUp = 1,
                                    PullDown = 2 };

    template <typename T>
    concept PinConfigTrait = requires {
        { T::Mode } -> std::convertible_to<PinMode>;
        { T::Pull } -> std::convertible_to<PinPull>;
        { T::OutputType } -> std::convertible_to<PinOutputType>;
        { T::Speed } -> std::convertible_to<PinSpeed>;
        { T::AlternateFunction } -> std::convertible_to<int>;
    };

    template <PinMode M = PinMode::Input, PinPull P = PinPull::None, PinOutputType O = PinOutputType::PushPull, PinSpeed S = PinSpeed::Low, int AF = -1>
    struct PinConfig {
        static constexpr PinMode Mode = M;
        static constexpr PinPull Pull = P;
        static constexpr PinOutputType OutputType = O;
        static constexpr PinSpeed Speed = S;
        static constexpr int AlternateFunction = AF;
    };

    template <typename T>
    concept PinTrait = requires {
        { T::set() } -> std::same_as<void>;
        { T::reset() } -> std::same_as<void>;
        { T::read() } -> std::convertible_to<bool>;
        T::template apply<PinConfig<>>();
    };
}