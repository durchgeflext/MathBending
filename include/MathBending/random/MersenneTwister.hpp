#pragma once
#include <cstddef>
#include <cstdint>

#include "MathBending/concepts/ScalarTypes.hpp"

namespace MathBending {

    template<U_INT_TYPE uint = uint32_t>
    //https://www.math.sci.hiroshima-u.ac.jp/m-mat/MT/ARTICLES/sfmt.pdf
    class SIMDFastMersenneTwister {
        static constexpr size_t N = 156; //upper(19937 / 128)

        static constexpr size_t stateSize() {
            return sizeof(uint128_t) / sizeof(uint) * N;
        }

        //https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine.html
        static constexpr uint32_t INIT_MUL_32 = 1812433253;

        uint seed;

        //TODO: Circular Array
        uint state[stateSize()];


        static constexpr size_t idxof(uint idx) {
            return idx % stateSize();
        }

        //TODO: Check Endianess for consistency
        static constexpr uint128_t linA(const uint128_t word) {
            return (word << 8) ^ word;
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
            return word >> 8;
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

        void init_state() {
            uint *state;
            size_t start = 0;
            if (sizeof(uint) <= sizeof(uint32_t)) {
                for (size_t i = 0; i < sizeof(uint32_t) / sizeof(uint); i++) {
                    this->state[i] = seed;
                }
                state = static_cast<uint32_t *>(this->state);
                start = 1;
            } else {
                this->state[0] = seed;
                state = static_cast<uint32_t*>(this->state);
                start = sizeof(uint128_t) / sizeof(uint);
            }

            for (; start < stateSize(); start++) {
                state[idxof(start)] = INIT_MUL_32 * (state[idxof(start - 1)] ^ state[idxof(start- 1)] >> 30) + start;
            }
        }

        public:

        SIMDFastMersenneTwister() : seed(0) {
            init_state();
        }

        explicit SIMDFastMersenneTwister(uint seed) : seed(seed) {
            init_state();
        }

        uint operator()() {
            //TODO: Implement!
            return static_cast<uint>(0);
        }

    };
}
