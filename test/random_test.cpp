#include "MathBending/random.hpp"

#include <iostream>

int main([[maybe_unused]]int argc, [[maybe_unused]]char** argv) {
    MathBending::SIMDFastMersenneTwister<uint32_t> rng(45);
    MathBending::SIMDFastMersenneTwister<uint32_t> rng2;
    std::cout << rng() << std::endl;
    std::cout << rng2() << std::endl << std::endl;

    std::cout << rng() << std::endl;
    std::cout << rng2() << std::endl << std::endl;

    std::cout << rng() << std::endl;
    std::cout << rng2() << std::endl << std::endl;

    std::cout << rng() << std::endl;
    std::cout << rng2() << std::endl << std::endl;

    std::cout << rng() << std::endl;
    std::cout << rng2() << std::endl << std::endl;

    return 0;
}
