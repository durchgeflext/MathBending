#pragma once
#include <cstddef>
#include <cstdint>

#include "MathBending/concepts/ScalarTypes.hpp"
#include "MathBending/functions/BitShifts.hpp"
#include "MathBending/util/CircularArray.hpp"

namespace MathBending {

    template<U_INT_TYPE uint = uint32_t>
    //https://www.math.sci.hiroshima-u.ac.jp/m-mat/MT/ARTICLES/sfmt.pdf
    class SIMDFastMersenneTwister {
        static constexpr size_t N = 156; //upper(19937 / 128)

        //https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine.html
        static constexpr uint32_t INIT_MUL_32 = 1812433253;
        static constexpr uint64_t INIT_MUL_64 = 6364136223846793005;

        static constexpr size_t POS_1 = 122;

        static constexpr size_t stateSize() {
            return sizeof(uint128_t) / sizeof(uint) * N;
        }

        //TODO: Check Endianess for consistency
        static constexpr uint128_t linA(const uint128_t word) {
            return (word << 8) ^ word;
        }

        static constexpr uint128_t linB(const uint128_t word) {
            auto result = sgmnt_bit_shift_r<uint128_t, uint32_t>(word, 11);
            result &= static_cast<uint128_t>(0xBFFFFFF6'BFFAFFFF) << 64 | static_cast<uint128_t>(0xDDFECB7F'DFFFFFEF);
            return result;
        }

        static constexpr uint128_t linC(const uint128_t word) {
            return word >> 8;
        }

        static constexpr uint128_t linD(const uint128_t word) {
            return sgmnt_bit_shift_l<uint128_t, uint32_t>(word, 18);
        }

        CircularArray<uint, stateSize()> state;
        size_t current = 0;
        uint seed;

        void init_state() {
            uint32_t init32 = seed;
            uint64_t init64 = seed;
            uint128_t init128 = seed;

            // Fill first 32 bits if necessary
            if constexpr (sizeof(uint) < sizeof(uint32_t)) {
                uint32_t last = seed;
                for (size_t i = 1; i < sizeof(uint32_t) / sizeof(uint); i++) {
                    last = static_cast<uint>(INIT_MUL_32) * (last ^ last >> (sizeof(uint) * 8 - 2)) + 1;
                    init32 |= last << (sizeof(uint) * 8);
                }
            }

            // Fill first 64bit if necessary
            if constexpr (sizeof(uint) < sizeof(uint64_t)) {
                init64 = static_cast<uint64_t>(INIT_MUL_32 * (init32 ^ init32 >> 30) + 1) << 32 | init32;
            }

            // Fill first 128bit if necessary
            if constexpr (sizeof(uint) < sizeof(uint128_t)) {
                init128 = static_cast<uint128_t>(INIT_MUL_64 * (init64 ^ init64 >> 62) + 1) << 64 | init64;
            }
            auto *state128 = reinterpret_cast<uint128_t*>(state.data());
            state128[0] = init128;

            //Fill other values
            for (size_t i = 1; i < N; i++) {
                state128[i] = INIT_MUL_64 * (state128[i -1] ^ state128[i - 1] >> 126) + i;
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
