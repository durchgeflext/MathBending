#pragma once
#include <cstddef>
#include <cstdint>

#include "MathBending/concepts/ScalarTypes.hpp"

namespace MathBending {

    template<U_INT_TYPE uint = uint32_t>
    //https://www.math.sci.hiroshima-u.ac.jp/m-mat/MT/ARTICLES/sfmt.pdf
    class SIMDFastMersenneTwister {
        uint seed;

        static constexpr uint128_t linA(const uint128_t word) {
            return (word << static_cast<uint128_t>(8)) + word;
        }

        static constexpr uint128_t linB(const uint128_t word) {
            const auto *p = reinterpret_cast<const uint32_t *>(&word);
            const uint32_t hi = (p[0] >> 11) & 0xBFFFFFF6;
            const uint32_t midHi = (p[1] >> 11) & 0xBFFAFFFF;
            const uint32_t midLo = (p[2] >> 11) & 0xDDFECB7F;
            const uint32_t lo = (p[3] >> 11) & 0xDFFFFFEF;

            uint128_t result;
            auto *r = reinterpret_cast<uint32_t *>(&result);

            r[0] = hi;
            r[1] = midHi;
            r[2] = midLo;
            r[3] = lo;

            return result;
        }

        static constexpr uint128_t linC(const uint128_t word) {
            return word >> static_cast<uint128_t>(8);
        }

        static constexpr uint128_t linD(const uint128_t word) {
            const auto *p = reinterpret_cast<const uint32_t *>(&word);
            const uint32_t hi = p[0] << 18;
            const uint32_t midHi = p[1] << 18;
            const uint32_t midLo = p[2] << 18;
            const uint32_t lo = p[3] << 18;

            uint128_t result = 0;
            auto *r = reinterpret_cast<uint32_t *>(&result);
            r[0] = hi;
            r[1] = midHi;
            r[2] = midLo;
            r[3] = lo;
            return result;
        }

        public:

        SIMDFastMersenneTwister() : seed(0) {}

        explicit SIMDFastMersenneTwister(uint seed) : seed(seed) {}

        uint operator()() {

            return static_cast<uint>(0);
        }

    };
}
