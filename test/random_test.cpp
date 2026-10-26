#include "MathBending/random.hpp"

#include <iostream>

int main([[maybe_unused]]int argc, [[maybe_unused]]char** argv) {
    MathBending::SIMDFastMersenneTwister<uint32_t> rng(45);
    MathBending::SIMDFastMersenneTwister<uint32_t> rng2;

    for (size_t i = 0; i < 1000; i++) {
        std::cout << rng() << std::endl;
        std::cout << rng2() << std::endl << std::endl;
    }

    return 0;
}
