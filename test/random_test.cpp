#include "MathBending/random.hpp"

#include <iostream>

int main([[maybe_unused]]int argc, [[maybe_unused]]char** argv) {
    MathBending::SIMDFastMersenneTwister<uint32_t> rng(45);
    std::cout << rng() << std::endl;
    std::cout << rng() << std::endl;
    std::cout << rng() << std::endl;
    std::cout << rng() << std::endl;
    std::cout << rng() << std::endl;

    return 0;
}
