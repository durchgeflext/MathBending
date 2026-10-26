#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "MathBending/random.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    const std::filesystem::path outPath
                = std::filesystem::path(MATHBENDING_PROJECT_ROOT) / "benchmark" / "files" / "sfmt.dat";
    std::fstream fileout(outPath, std::ios_base::out | std::ios_base::binary);
    if (fileout.rdstate() == std::ios_base::failbit) {
        std::cerr << "Opening the filestream failed. Is the path correct?" << std::endl;
    }
    size_t samples = 1'000;
    if (argc == 2) {
        samples = std::stoi(argv[1]);
    }
    MathBending::SIMDFastMersenneTwister rng(uint32_t{0});
    for (size_t i = 0; i < samples; i++) {
        uint32_t value = rng();
        fileout.write(reinterpret_cast<char*>(&value), sizeof(uint32_t));
    }
    fileout.close();
    if (fileout.rdstate() == std::ios_base::failbit) {
        std::cerr << "Closing the file produced an error" << std::endl;
    }
}
