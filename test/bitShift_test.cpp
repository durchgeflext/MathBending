
#include "MathBending/functions/BitShifts.hpp"
#include "MathBending/util/Integer128.hpp"

int main([[maybe_unused]]int argc, [[maybe_unused]]char** argv) {
    uint128_t test1 = 0;
    uint128_t test2 = 0;

    test1 = bit_shift_l<uint128_t>(test1, 0);
    if (test1 != 0) return 1;
    test2 = bit_shift_r<uint128_t>(test2, 0);
    if (test2 != 0) return 2;
    return 0;
}