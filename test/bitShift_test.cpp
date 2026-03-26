
#include <catch2/catch_test_macros.hpp>

#include "MathBending/functions/BitShifts.hpp"
#include "MathBending/util/Integer128.hpp"

TEST_CASE("Segment shifting does not change 0", "[Segment Bit Shift 0]") {
    SECTION("Segment Shifting uint128_t{0}") {
        REQUIRE(sgmnt_bit_shift_l<uint128_t, uint128_t>(uint128_t(0), 1) == uint128_t(0));
        REQUIRE(sgmnt_bit_shift_r<uint128_t, uint128_t>(uint128_t(0), 1) == uint128_t(0));

        REQUIRE(sgmnt_bit_shift_l<uint128_t, uint64_t>(uint128_t(0), 1) == uint128_t(0));
        REQUIRE(sgmnt_bit_shift_r<uint128_t, uint64_t>(uint128_t(0), 1) == uint128_t(0));

        REQUIRE(sgmnt_bit_shift_l<uint128_t, uint32_t>(uint128_t(0), 1) == uint128_t(0));
        REQUIRE(sgmnt_bit_shift_r<uint128_t, uint32_t>(uint128_t(0), 1) == uint128_t(0));

        REQUIRE(sgmnt_bit_shift_l<uint128_t, uint16_t>(uint128_t(0), 1) == uint128_t(0));
        REQUIRE(sgmnt_bit_shift_r<uint128_t, uint16_t>(uint128_t(0), 1) == uint128_t(0));

        REQUIRE(sgmnt_bit_shift_l<uint128_t, uint8_t>(uint128_t(0), 1) == uint128_t(0));
        REQUIRE(sgmnt_bit_shift_r<uint128_t, uint8_t>(uint128_t(0), 1) == uint128_t(0));
    }

    SECTION("Segment Shifting uint64_t{0}") {
        REQUIRE(sgmnt_bit_shift_l<uint64_t, uint64_t>(uint128_t(0), 1) == uint128_t(0));
        REQUIRE(sgmnt_bit_shift_r<uint64_t, uint64_t>(uint128_t(0), 1) == uint128_t(0));

        REQUIRE(sgmnt_bit_shift_l<uint64_t, uint32_t>(uint128_t(0), 1) == uint128_t(0));
        REQUIRE(sgmnt_bit_shift_r<uint64_t, uint32_t>(uint128_t(0), 1) == uint128_t(0));

        REQUIRE(sgmnt_bit_shift_l<uint64_t, uint16_t>(uint128_t(0), 1) == uint128_t(0));
        REQUIRE(sgmnt_bit_shift_r<uint64_t, uint16_t>(uint128_t(0), 1) == uint128_t(0));

        REQUIRE(sgmnt_bit_shift_l<uint64_t, uint8_t>(uint128_t(0), 1) == uint128_t(0));
        REQUIRE(sgmnt_bit_shift_r<uint64_t, uint8_t>(uint128_t(0), 1) == uint128_t(0));
    }

    SECTION("Segment Shifting uint32_t{0}") {
        REQUIRE(sgmnt_bit_shift_l<uint32_t, uint32_t>(uint128_t(0), 1) == uint128_t(0));
        REQUIRE(sgmnt_bit_shift_r<uint32_t, uint32_t>(uint128_t(0), 1) == uint128_t(0));

        REQUIRE(sgmnt_bit_shift_l<uint32_t, uint16_t>(uint128_t(0), 1) == uint128_t(0));
        REQUIRE(sgmnt_bit_shift_r<uint32_t, uint16_t>(uint128_t(0), 1) == uint128_t(0));

        REQUIRE(sgmnt_bit_shift_l<uint32_t, uint8_t>(uint128_t(0), 1) == uint128_t(0));
        REQUIRE(sgmnt_bit_shift_r<uint32_t, uint8_t>(uint128_t(0), 1) == uint128_t(0));
    }

    SECTION("Segment Shifting uint16_t{0}") {
        REQUIRE(sgmnt_bit_shift_l<uint16_t, uint16_t>(uint128_t(0), 1) == uint128_t(0));
        REQUIRE(sgmnt_bit_shift_r<uint16_t, uint16_t>(uint128_t(0), 1) == uint128_t(0));

        REQUIRE(sgmnt_bit_shift_l<uint16_t, uint8_t>(uint128_t(0), 1) == uint128_t(0));
        REQUIRE(sgmnt_bit_shift_r<uint16_t, uint8_t>(uint128_t(0), 1) == uint128_t(0));
    }

    SECTION("Segment Shifting uint8_t{0}") {
        REQUIRE(sgmnt_bit_shift_l<uint8_t, uint8_t>(uint128_t(0), 1) == uint128_t(0));
        REQUIRE(sgmnt_bit_shift_r<uint8_t, uint8_t>(uint128_t(0), 1) == uint128_t(0));
    }

}

TEST_CASE("Left Segment shifting will shift out bits at each segment border", "[Segment Bit Shift_l segments]") {
    constexpr uint8_t left8 = 0x80;
    constexpr uint16_t left16 = static_cast<uint16_t>(left8) << 8 | left8;
    constexpr uint32_t left32 = static_cast<uint32_t>(left16) << 16 | left16;
    constexpr uint64_t left64 = static_cast<uint64_t>(left32) << 32 | left32;
    constexpr uint128_t left128 = static_cast<uint128_t>(left64) << 64 | left64;

    SECTION("Left Segment Shifting 8 bit segments") {
        REQUIRE(sgmnt_bit_shift_l<uint8_t, uint8_t>(left8, 1) == 0);
        REQUIRE(sgmnt_bit_shift_l<uint16_t, uint8_t>(left16, 1) == 0);
        REQUIRE(sgmnt_bit_shift_l<uint32_t, uint8_t>(left32, 1) == 0);
        REQUIRE(sgmnt_bit_shift_l<uint64_t, uint8_t>(left64, 1) == 0);
        REQUIRE(sgmnt_bit_shift_l<uint128_t, uint8_t>(left128, 1) == 0);
    }

    SECTION("Left Segment Shifting 16 bit segments") {
        REQUIRE(sgmnt_bit_shift_l<uint16_t, uint16_t>(left16, 1) == 0x0100);
        REQUIRE(sgmnt_bit_shift_l<uint32_t, uint16_t>(left32, 1) == 0x0100'0100);
        REQUIRE(sgmnt_bit_shift_l<uint64_t, uint16_t>(left64, 1) == 0x0100'0100'0100'0100);
        //TODO: Make it work on windows
        REQUIRE(sgmnt_bit_shift_l<uint128_t, uint16_t>(left128, 1) == (uint128_t(0x0100'0100'0100'0100) << 64 | 0x0100'0100'0100'0100));
    }

    SECTION("Left Segment Shifting 32 bit segments") {
        REQUIRE(sgmnt_bit_shift_l<uint32_t, uint32_t>(left32, 1) == 0x0101'0100);
        REQUIRE(sgmnt_bit_shift_l<uint64_t, uint32_t>(left64, 1) == 0x0101'0100'0101'0100);
        //TODO: Make it work on windows
        REQUIRE(sgmnt_bit_shift_l<uint128_t, uint32_t>(left128, 1) == (uint128_t(0x0101'0100'0101'0100) << 64 | 0x0101'0100'0101'0100));
    }

    SECTION("Left Segment Shifting 64 bit segment") {
        REQUIRE(sgmnt_bit_shift_l<uint64_t, uint64_t>(left64, 1) == 0x0101'0101'0101'0100);
        //TODO: Make it work on windows
        REQUIRE(sgmnt_bit_shift_l<uint128_t, uint64_t>(left128, 1) == (uint128_t(0x0101'0101'0101'0100) << 64 | 0x0101'0101'0101'0100));
    }

    SECTION("Left Segment Shifting 128 bit segment") {
        //TODO: Make it work on windows
        REQUIRE(sgmnt_bit_shift_l<uint128_t, uint128_t>(left128, 1) == (uint128_t(0x0101'0101'0101'0101) << 64 | 0x0101'0101'0101'0100));
    }
}