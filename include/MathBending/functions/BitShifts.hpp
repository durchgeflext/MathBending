#pragma once

#include <cstddef>

#include "MathBending/concepts/ScalarTypes.hpp"
#include "MathBending/util/Integer128.hpp"

template<U_INT_TYPE T>
static constexpr uint128_t bit_shift_l(const uint128_t word, const size_t shift) {
    if (sizeof(T) == sizeof(word)) return word << shift;
    uint128_t result = 0;
    const T* parts = reinterpret_cast<const T*>(&word);
    T* resParts = reinterpret_cast<T*>(&result);
    for (size_t i = 0; i < sizeof(word)/sizeof(T); i++) {
        resParts[i] = parts[i] << shift;
    }
    return result;
}

template<U_INT_TYPE T>
static constexpr uint128_t bit_shift_r(const uint128_t word, const size_t shift) {
    if (sizeof(T) == sizeof(word)) return word >> shift;
    uint128_t result = 0;
    const T* parts = reinterpret_cast<const T*>(&word);
    T* resParts = reinterpret_cast<T*>(&result);
    for (size_t i = 0; i < sizeof(word)/sizeof(T); i++) {
        resParts[i] = parts[i] >> shift;
    }
    return result;
}