#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <thread>

#include "MathBending/random/MersenneTwister.hpp"

int main(int argc, char** argv) {
    size_t samples = 50'000'000;
    if (argc >= 2) {
        samples = std::stoi(argv[1]);
    }
    std::mt19937 stdMT_32;
    MathBending::SIMDFastMersenneTwister<uint32_t> sfmt_32;

    std::cout << "Sleeping..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    //------------------32 bit std::mt19937----------------------
    std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
    uint32_t sum32 = 0;
    for (size_t i = 0; i < samples; i++) {
        sum32 += stdMT_32();
    }
    std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
    double elapsed =
        static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()) / 1'000;
    std::cout << std::fixed << std::setprecision(3) << "Generating " << samples
              << " random 32 bit numbers using std::mt19937 took " << elapsed << " ms" << std::endl;

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
        static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()) / 1'000;
    std::cout << std::fixed << std::setprecision(3) << "Generating " << samples
              << " random 32 bit numbers using MathBending::SFMT took " << elapsed << " ms" << std::endl;


    std::mt19937_64 stdMT_64;
    MathBending::SIMDFastMersenneTwister<uint64_t> sfmt_64;

    std::cout << "Sleeping..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    //------------------64 bit std::mt19937----------------------
    start = std::chrono::high_resolution_clock::now();
    uint64_t sum64 = 0;
    for (size_t i = 0; i < samples; i++) {
        sum64 += stdMT_64();
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed =
        static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()) / 1'000;
    std::cout << std::fixed << std::setprecision(3) << "Generating " << samples
              << " random 64 bit numbers using std::mt19937 took " << elapsed << " ms" << std::endl;

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
        static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()) / 1'000;
    std::cout << std::fixed << std::setprecision(3) << "Generating " << samples
              << " random 64 bit numbers using MathBending::SFMT took " << elapsed << " ms" << std::endl;
}
