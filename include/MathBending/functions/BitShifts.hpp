#pragma once

#include "MathBending/util/Integer128.hpp"

template<U_INT_TYPE T>
static constexpr uint128_t bit_shift_l(const uint128_t word, const size_t shift) {
    if (sizeof(T) == sizeof(word)) return word << shift;
    T parts[sizeof(word) / sizeof(T)] = &word;
    for (size_t i = 0; i < sizeof(word)/sizeof(T); i++) {
        parts[i] << shift;
    }
    return *reinterpret_cast<uint128_t*>(parts);
}

template<U_INT_TYPE T>
static constexpr uint128_t bit_shift_r(const uint128_t word, const size_t shift) {
    if (sizeof(T) == sizeof(word)) return word >> shift;
    T parts[sizeof(word) / sizeof(T)] = &word;
    for (size_t i = 0; i < sizeof(word)/sizeof(T); i++) {
        parts[i] >> shift;
    }
    return *reinterpret_cast<uint128_t*>(parts);
}