#pragma once
#include <cstdint>

#include "MathBending/concepts/ScalarTypes.hpp"

namespace MathBending {

    template<U_INT_TYPE uint = uint32_t>
    //https://www.math.sci.hiroshima-u.ac.jp/m-mat/MT/ARTICLES/sfmt.pdf
    class SIMDFastMersenneTwister {
        uint seed;

        public:

        SIMDFastMersenneTwister() : seed(0) {}

        explicit SIMDFastMersenneTwister(uint seed) : seed(seed) {}

        uint operator()() {

            return static_cast<uint>(0);
        }

    };
}
