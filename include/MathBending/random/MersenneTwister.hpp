#pragma once
#include <cstddef>
#include <cstdint>

#include "MathBending/concepts/ScalarTypes.hpp"
#include "MathBending/util/CircularArray.hpp"

namespace MathBending {

    template<U_INT_TYPE uint = uint32_t>
    //https://www.math.sci.hiroshima-u.ac.jp/m-mat/MT/ARTICLES/sfmt.pdf
    class SIMDFastMersenneTwister {
        static constexpr size_t N = 156; //upper(19937 / 128)

        //https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine.html
        static constexpr uint32_t INIT_MUL_32 = 1812433253;

        static constexpr size_t POS_1 = 122;

        static constexpr size_t stateSize() {
            return sizeof(uint128_t) / sizeof(uint) * N;
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

        CircularArray<uint, stateSize()> state;
        size_t current = 0;
        uint seed;

        void init_state() {
            uint *tmp_state = this->state.data();
            size_t start = 0;
            if (sizeof(uint) <= sizeof(uint32_t)) {
                for (size_t i = 0; i < sizeof(uint32_t) / sizeof(uint); i++) {
                    this->state[i] = seed;
                }
                start = 1;
            } else {
                this->state[0] = seed;
                start = sizeof(uint128_t) / sizeof(uint);
            }

            for (; start < stateSize(); start++) {
                tmp_state[start] = INIT_MUL_32 * (tmp_state[start - 1] ^ tmp_state[start - 1] >> 30) + start;
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
            if (current % (sizeof(uint128_t) / sizeof(uint)) == 0) {
                //Update
                const uint128_t a = linA(*static_cast<uint128_t*>(static_cast<void*>(state.data(current))));
                const uint128_t b = linB(*static_cast<uint128_t*>(static_cast<void*>(state.data(current + POS_1))));
                const uint128_t c = linC(*static_cast<uint128_t*>(static_cast<void*>(state.data(current + stateSize() - 2))));
                const uint128_t d = linD(*static_cast<uint128_t*>(static_cast<void*>(state.data(current + stateSize() - 1))));
                *static_cast<uint128_t*>(static_cast<void*>(state.data(current))) = a + b + c + d;
            }
            uint tmp = state[current];
            current = state.next(current);
            return tmp;
        }

        uint getSeed() const {
            return seed;
        }

    };
}
