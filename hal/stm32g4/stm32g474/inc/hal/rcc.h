#pragma once
#include "hal/core/rcc.h"
#include "hal/systick.h"
#include "hal/utils.h"
#include "logger.h"
#include "stm32g474xx.h"
#include "system_stm32g4xx.h"
#include <concepts>
#include <cstdint>
#include <initializer_list>
#include <cstdio>

namespace hal::rcc {
    template <typename T>
    concept PllClkSrcTrait = requires {
        { T::freq } -> std::convertible_to<uint32_t>;
        { T::pllSrcFlag } -> std::convertible_to<uint32_t>;
        { T::enable() } -> std::same_as<void>;
    };

    template <typename T>
    concept PllTrait = requires {
        { T::m } -> std::convertible_to<uint32_t>;
        { T::n } -> std::convertible_to<uint32_t>;
        { T::r } -> std::convertible_to<uint32_t>;
        { T::p } -> std::convertible_to<uint32_t>;
        { T::q } -> std::convertible_to<uint32_t>;
        { T::vco } -> std::convertible_to<uint32_t>;

        { T::init() } -> std::same_as<void>;
    };

    template <typename T>
    concept SysClkSrcTrait = requires {
        { T::freq } -> std::convertible_to<uint32_t>;
        { T::sysClkSrcFlag } -> std::convertible_to<uint32_t>;
        { T::sysClkStatusFlag } -> std::convertible_to<uint32_t>;
        { T::enable() } -> std::same_as<void>;
    };

    template <uint32_t srcFreq, uint32_t dstFreq>
    struct PllAutoSolver {
        struct Result {
            uint32_t m, n, r;
            uint32_t error;
            bool valid;
        };

        static consteval Result solve() {
            Result best{0, 0, 0, UINT32_MAX, false};

            for (uint32_t m = 1; m <= 16; m++) {
                auto pll_in = srcFreq / m;

                if (pll_in < 2'660'000 || pll_in > 16'000'000)
                    continue;

                for (uint32_t n = 8; n <= 127; n++) {
                    auto vco = pll_in * n;
                    if (vco < 96'000'000 || vco > 344'000'000)
                        continue;

                    for (uint32_t r : {2u, 4u, 6u, 8u}) {
                        auto sys = vco / r;
                        auto error = (sys > dstFreq) ? (sys - dstFreq) : (dstFreq - sys);

                        if (error < best.error) {
                            best = {m, n, r, error, true};

                            if (error == 0)
                                return best;
                        }
                    }
                }
            }

            return best;
        }
    };

    struct HSI {
        static constexpr uint32_t freq = 16'000'000;
        static constexpr uint32_t pllSrcFlag = RCC_PLLCFGR_PLLSRC_HSI;
        static constexpr uint32_t sysClkSrcFlag = RCC_CFGR_SW_HSI;
        static constexpr uint32_t sysClkStatusFlag = RCC_CFGR_SWS_HSI;

        static inline void enable() {
            RCC->CR |= RCC_CR_HSION;

            while (!(RCC->CR & RCC_CR_HSIRDY)) {
            }
        }
    };

    template <HzTrait Freq>
    struct HSE {
        static_assert(Freq::hz >= 4'000'000 && Freq::hz <= 48'000'000, "HSE Frequency needs to be between 4MHz and 48MHz");

        static constexpr uint32_t freq = Freq::hz;
        static constexpr uint32_t pllSrcFlag = RCC_PLLCFGR_PLLSRC_HSE;
        static constexpr uint32_t sysClkSrcFlag = RCC_CFGR_SW_HSE;
        static constexpr uint32_t sysClkStatusFlag = RCC_CFGR_SWS_HSE;

        static inline void enable() {
            RCC->CR |= RCC_CR_HSEON;

            while (!(RCC->CR & RCC_CR_HSERDY)) {
            }
        }
    };

    template <PllClkSrcTrait Source, uint32_t M, uint32_t N, uint32_t R, uint32_t Q = 2, uint32_t P = 2>
    struct PLL {
        static_assert(P >= 2 && P <= 31, "P must be between 2 and 31");
        static_assert(R >= 2 && R <= 8 && R % 2 == 0, "R must be one of 2,4,6,8");
        static_assert(Q >= 2 && Q <= 8 && Q % 2 == 0, "Q must be one of 2,4,6,8");
        static_assert(N >= 8 && N <= 127, "N must be between 8 and 127");
        static_assert(M >= 1 && M <= 16, "M must be between 1 and 16");

        static constexpr uint32_t m = M;
        static constexpr uint32_t n = N;
        static constexpr uint32_t r = R;
        static constexpr uint32_t q = Q;
        static constexpr uint32_t p = P;

        static constexpr uint32_t vco = Source::freq * N / M;

        static constexpr bool boostMode = vco / r > 150'000'000 || vco / q > 150'000'000 || vco / p > 150'000'000;

        static_assert(vco >= 96'000'000 && vco <= 344'000'000, "VCO must be between 96MHz and 344MHz");
        static_assert(Source::freq / M >= 2'660'000 && Source::freq / M <= 16'000'000, "PLL input needs to be between 2.66MHz and 16MHz");

        static inline void init() {
            Source::enable();

            RCC->CR &= ~RCC_CR_PLLON;

            RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLPDIV_Msk;
            RCC->PLLCFGR |= P << RCC_PLLCFGR_PLLPDIV_Pos;

            RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLR_Msk;
            RCC->PLLCFGR |= (R / 2 - 1) << RCC_PLLCFGR_PLLR_Pos;

            RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLQ_Msk;
            RCC->PLLCFGR |= (Q / 2 - 1) << RCC_PLLCFGR_PLLQ_Pos;

            RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN_Msk;
            RCC->PLLCFGR |= N << RCC_PLLCFGR_PLLN_Pos;

            RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM_Msk;
            RCC->PLLCFGR |= (M - 1) << RCC_PLLCFGR_PLLM_Pos;

            RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLSRC_Msk;
            RCC->PLLCFGR |= Source::pllSrcFlag;

            RCC->CR |= RCC_CR_PLLON;
            while (!(RCC->CR & RCC_CR_PLLRDY)) {
            }
        }
    };

    template <PllClkSrcTrait Source, HzTrait Target>
    struct PLLAuto {
    private:
        static constexpr auto result = PllAutoSolver<Source::freq, Target::hz>::solve();

        static_assert(result.valid, "No valid PLL configuration found");

    public:
        static constexpr uint32_t m = result.m;
        static constexpr uint32_t n = result.n;
        static constexpr uint32_t r = result.r;
        static constexpr uint32_t q = 2;
        static constexpr uint32_t p = 2;

        static constexpr uint32_t vco = Source::freq * n / m;

        static inline void init() {
            PLL<Source, m, n, r, q, p>::init();
        }
    };

    template <PllTrait T>
    struct PLLR {
        static constexpr uint32_t freq = T::vco / T::r;
        static constexpr uint32_t sysClkSrcFlag = RCC_CFGR_SW_PLL;
        static constexpr uint32_t sysClkStatusFlag = RCC_CFGR_SWS_PLL;

        static_assert(freq >= 8'000'000 && freq <= 170'000'000, "PLLQ-Clock must be between 8MHz and 170MHz");

        static inline void enable() {
            RCC->PLLCFGR |= RCC_PLLCFGR_PLLREN;
        }
    };

    template <PllTrait T>
    struct PLLQ {
        static constexpr uint32_t freq = T::vco / T::q;

        static_assert(freq >= 8'000'000 && freq <= 170'000'000, "PLLQ-Clock must be between 8MHz and 170MHz");

        static inline void enable() {
            RCC->PLLCFGR |= RCC_PLLCFGR_PLLQEN;
        }
    };

    template <PllTrait T>
    struct PLLP {
        static constexpr uint32_t freq = T::vco / T::p;

        static_assert(freq >= 2'064'500 && freq <= 170'000'000, "PLLP-Clock must be between 2.0645MHz and 170MHz");

        static inline void enable() {
            RCC->PLLCFGR |= RCC_PLLCFGR_PLLPEN;
        }
    };

    template <PllTrait PLL, SysClkSrcTrait SysClockSource>
    struct ClockConfig {
        static_assert(SysClockSource::freq >= 8'000'000 && SysClockSource::freq <= 170'000'000, "SysClk must be between 8MHz and 170MHz");

        static constexpr uint32_t sysclk = SysClockSource::freq;
        static constexpr uint32_t pclk = SysClockSource::freq;

        /// @brief Initialize the Clocktree
        static void init() {
            // Switch sysclk to HSI while setting up the clock tree
            RCC->CFGR &= ~RCC_CFGR_SW_Msk;
            RCC->CFGR |= RCC_CFGR_SW_HSI;

            while (!(RCC->CFGR & RCC_CFGR_SWS_HSI)) {
            }

            static constexpr bool transition = SysClockSource::freq > 80'000'000;
            static constexpr bool boostMode = SysClockSource::freq > 150'000'000;
            static constexpr uint32_t waitStates = getFlashWaitStates(SysClockSource::freq, boostMode);

            // Initialize pll first
            PLL::init();

            if constexpr (transition) {
                // Transition phase needed
                setFlashWaitStates(waitStates);
            }

            if constexpr (boostMode) {
                PWR->CR5 &= ~PWR_CR5_R1MODE;
            } else {
                PWR->CR5 |= PWR_CR5_R1MODE;
            }

            if (SysClockSource::freq > getSystemCoreClock()) {
                // Speed increase: Set new wait states first
                setFlashWaitStates(waitStates);
            }

            RCC->CFGR &= ~RCC_CFGR_SW_Msk;
            RCC->CFGR |= SysClockSource::sysClkSrcFlag;
            while (!(RCC->CFGR & SysClockSource::sysClkStatusFlag)) {
            }

            if constexpr (transition) {
                hal::systick::init(SysClockSource::freq / 2);
                hal::systick::delay_ms(1);

                RCC->CFGR &= ~RCC_CFGR_HPRE_Msk;
                while (RCC->CFGR & RCC_CFGR_HPRE_Msk) {
                }
            }

            hal::systick::init(SysClockSource::freq);

            if (SysClockSource::freq < getSystemCoreClock()) {
                // Speed decrease: Set new wait states after change
                FLASH->ACR &= ~FLASH_ACR_LATENCY_Msk;
                FLASH->ACR |= waitStates << FLASH_ACR_LATENCY_Pos;

                while (((FLASH->ACR & FLASH_ACR_LATENCY_Msk) >> FLASH_ACR_LATENCY_Pos) != waitStates) {
                }
            }

            SystemCoreClockUpdate();

            char buf[128]{0};
            snprintf(buf, sizeof(buf), "Clock configured: SysClk [%.4f MHz]", SysClockSource::freq / 1000.0 / 1000.0);
            logger::debug(buf);
        }

    private:
        static inline void setFlashWaitStates(uint32_t waitStates) {
            FLASH->ACR &= ~FLASH_ACR_LATENCY_Msk;
            FLASH->ACR |= waitStates << FLASH_ACR_LATENCY_Pos;

            while (((FLASH->ACR & FLASH_ACR_LATENCY_Msk) >> FLASH_ACR_LATENCY_Pos) != waitStates) {
            }
        }

        static consteval uint32_t getFlashWaitStates(uint32_t freq, bool boostMode) {
            uint32_t waitStates = 0;

            if (boostMode) {
                if (freq <= 34'000'000) {
                    waitStates = 0;
                } else if (freq <= 68'000'000) {
                    waitStates = 1;
                } else if (freq <= 102'000'000) {
                    waitStates = 2;
                } else if (freq <= 136'000'000) {
                    waitStates = 3;
                } else {
                    waitStates = 4;
                }
            } else {
                if (freq <= 30'000'000) {
                    waitStates = 0;
                } else if (freq <= 60'000'000) {
                    waitStates = 1;
                } else if (freq <= 90'000'000) {
                    waitStates = 2;
                } else if (freq <= 120'000'000) {
                    waitStates = 3;
                } else {
                    waitStates = 4;
                }
            }

            return waitStates;
        }
    };
}