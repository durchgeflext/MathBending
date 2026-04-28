#include <cstddef>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "MathBending/random.hpp"

int main([[maybe_unused]]int argc, [[maybe_unused]]char** argv) {
    MathBending::VanDerCorputSequence<float, 10> vdcSeq;
    std::stringstream out;
    out << std::fixed << std::setprecision(4);
    for (size_t i = 0; i < 200; i++) {
        out << std::to_string(vdcSeq()) << ",";
        if ((i + 1) % 10 == 0) out << std::endl;
        if ((i + 1) % 100 == 0) out << std::endl;
    }

    out << std::endl << std::endl << "Static version" << std::endl << std::endl;
    for (size_t i = 0; i < 200; i++) {
        out << std::to_string(MathBending::VanDerCorputSequence<float,10>::vanDerCorput(i));
        out << ",";
        if ((i + 1) % 10 == 0) out << std::endl;
        if ((i + 1) % 100 == 0) out << std::endl;
    }

    std::cout << out.str();

}
