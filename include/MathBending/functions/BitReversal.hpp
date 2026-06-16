#pragma once
#include "MathBending/concepts/ScalarTypes.hpp"

static constexpr uint8_t reverse_bits_8(uint8_t word) {
    word = word << 4 | word >> 4;
    word = (word & 0x33) << 2 | (word & 0xcc) >> 1;
    word = (word & 0x55) << 1 | (word & 0xaa) >> 1;
    return word;
}

static constexpr uint16_t reverse_bits_16(uint16_t word) {
    word = word << 8 | word >> 8;
    word = (word & 0x0f0f) << 4 | (word & 0xf0f0) >> 4;
    word = (word & 0x3333) << 2 | (word & 0xcccc) >> 2;
    word = (word & 0x5555) << 1 | (word & 0xaaaa) >> 1;
    return word;
}

static constexpr uint32_t reverse_bits_32(uint32_t word) {
    word = word << 16 | word >> 16;
    word = (word & 0x00ff00ff) << 8 | (word & 0xff00ff00) >> 8;
    word = (word & 0x0f0f0f0f) << 4 | (word & 0xf0f0f0f0) >> 4;
    word = (word & 0x33333333) << 2 | (word & 0xcccccccc) >> 2;
    word = (word & 0x55555555) << 1 | (word & 0xaaaaaaaa) >> 1;
    return word;
}

static constexpr uint64_t reverse_bits_64(uint64_t word) {
    word = word << 32 | word >> 32;
    word = (word & 0x0000ffff0000ffff) << 16 | (word & 0xffff0000ffff0000) >> 16;
    word = (word & 0x00ff00ff00ff00ff) << 8  | (word & 0xff00ff00ff00ff00) >> 8;
    word = (word & 0x0f0f0f0f0f0f0f0f) << 4  | (word & 0xf0f0f0f0f0f0f0f0) >> 4;
    word = (word & 0x3333333333333333) << 2  | (word & 0xcccccccccccccccc) >> 2;
    word = (word & 0x5555555555555555) << 1  | (word & 0xaaaaaaaaaaaaaaaa) >> 1;
    return word;
}

static constexpr uint128_t reverse_bits_128(uint128_t word) {
    word = word << 64 | word >> 64;
    word = (word & (uint128_t{0x00000000ffffffff} << 64) | uint128_t{0x00000000ffffffff}) << 32 |
           (word & (uint128_t{0xffffffff00000000} << 64) | uint128_t{0xffffffff00000000}) >> 32;
    word = (word & (uint128_t{0x0000ffff0000ffff} << 64) | uint128_t{0x0000ffff0000ffff}) << 16 |
           (word & (uint128_t{0xffff0000ffff0000} << 64) | uint128_t{0xffff0000ffff0000}) >> 16;
    word = (word & (uint128_t{0x00ff00ff00ff00ff} << 64) | uint128_t{0x00ff00ff00ff00ff}) << 8 |
           (word & (uint128_t{0xff00ff00ff00ff00} << 64) | uint128_t{0xff00ff00ff00ff00}) >> 8;
    word = (word & (uint128_t{0x0f0f0f0f0f0f0f0f} << 64) | uint128_t{0x0f0f0f0f0f0f0f0f}) >> 4 |
           (word & (uint128_t{0xf0f0f0f0f0f0f0f0} << 64) | uint128_t{0xf0f0f0f0f0f0f0f0}) << 4;
    word = (word & (uint128_t{0x3333333333333333} << 64) | uint128_t{0x3333333333333333}) >> 4 |
           (word & (uint128_t{0xcccccccccccccccc} << 64) | uint128_t{0xcccccccccccccccc}) << 4;
    word = (word & (uint128_t{0x5555555555555555} << 64) | uint128_t{0x5555555555555555}) >> 4 |
           (word & (uint128_t{0xaaaaaaaaaaaaaaaa} << 64) | uint128_t{0xaaaaaaaaaaaaaaaa}) << 4;
    return word;
}
