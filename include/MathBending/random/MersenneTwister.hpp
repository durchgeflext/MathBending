#pragma once
#include <cstdint>

namespace MathBending {

    class MersenneTwister32 {
        uint32_t seed;

        public:
        explicit MersenneTwister32(const uint32_t seed) : seed(seed) {

        }

        uint32_t operator() () {
            return 0;
        }
    };

    class MersenneTwister64 {
        uint64_t seed;

        public:
        explicit MersenneTwister64(const uint64_t seed) : seed(seed) {

        }

        uint64_t operator()() {

            return 0ull;
        }

    };
}
