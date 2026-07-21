#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <thread>

#include "MathBending/random/MersenneTwister.hpp"

int main(int argc, char** argv) {
    size_t samples = 1'000;
    if (argc >= 2) {
        samples = std::stoi(argv[1]);
    }
    std::mt19937 stdMT_32;
    MathBending::SIMDFastMersenneTwister<uint32_t> sfmt_32;

    //------------------32 bit std::mt19937----------------------
    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::high_resolution_clock::now();
    uint32_t sum32 = 0;
    for (size_t i = 0; i < samples; i++) {
        sum32 += stdMT_32();
    }
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::high_resolution_clock::now();
    double elapsed =
        static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
    std::cout << std::setprecision(4) << "Generating " << std::to_string(samples)
              << " random 32 bit numbers using std::mt19937 took " << std::to_string(elapsed) << "µs" << std::endl;

    std::cout << "Sleeping..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    //--------------------32 bit sfmt------------------------------
    start = std::chrono::high_resolution_clock::now();
    sum32 = 0;
    for (size_t i = 0; i < samples; i++) {
        sum32 += sfmt_32();
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed =
        static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
    std::cout << std::setprecision(4) << "Generating " << std::to_string(samples)
              << " random 32 bit numbers using MathBending::SFMT took " << std::to_string(elapsed) << "µs" << std::endl;

    std::cout << "Sleeping..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));


    std::mt19937_64 stdMT_64;
    MathBending::SIMDFastMersenneTwister<uint64_t> sfmt_64;

    //------------------64 bit std::mt19937----------------------
    start = std::chrono::high_resolution_clock::now();
    uint64_t sum64 = 0;
    for (size_t i = 0; i < samples; i++) {
        sum64 += stdMT_64();
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed =
        static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
    std::cout << std::setprecision(4) << "Generating " << std::to_string(samples)
              << " random 64 bit numbers using std::mt19937 took " << std::to_string(elapsed) << "µs" << std::endl;

    std::cout << "Sleeping..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    //--------------------64 bit sfmt------------------------------
    start = std::chrono::high_resolution_clock::now();
    sum64 = 0;
    for (size_t i = 0; i < samples; i++) {
        sum64 += sfmt_64();
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed =
        static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
    std::cout << std::setprecision(4) << "Generating " << std::to_string(samples)
              << " random 64 bit numbers using MathBending::SFMT took " << std::to_string(elapsed) << "ns" << std::endl;
}
