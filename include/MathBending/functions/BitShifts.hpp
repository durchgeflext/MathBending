#pragma once

#include <cstddef>

#include "MathBending/concepts/ScalarTypes.hpp"
#include "MathBending/util/Integer128.hpp"

template<U_INT_TYPE word_t, U_INT_TYPE sgmnt_t>
static constexpr word_t sgmnt_bit_shift_l(const word_t word, const size_t shift) {
    static_assert(sizeof(sgmnt_t) <= sizeof(word_t), "The segment size cannot be greater than the word size");

    if (sizeof(sgmnt_t) == sizeof(word_t)) return word << shift;
    word_t result = 0;
    const auto* parts = reinterpret_cast<const sgmnt_t*>(&word);
    auto* resParts = reinterpret_cast<sgmnt_t*>(&result);
    for (size_t i = 0; i < sizeof(word_t) / sizeof(sgmnt_t); i++) {
        resParts[i] = parts[i] << shift;
    }
    return result;
}

template<U_INT_TYPE word_t, U_INT_TYPE sgmnt_t>
static constexpr word_t sgmnt_bit_shift_r(const word_t word, const size_t shift) {
    static_assert(sizeof(sgmnt_t) <= sizeof(word_t), "The segment size cannot be greater than the word size");

    if (sizeof(sgmnt_t) == sizeof(word_t)) return word >> shift;
    word_t result = 0;
    const auto* parts = reinterpret_cast<const sgmnt_t*>(&word);
    auto* resParts = reinterpret_cast<sgmnt_t*>(&result);
    for (size_t i = 0; i < sizeof(word_t) / sizeof(sgmnt_t); i++) {
        resParts[i] = parts[i] >> shift;
    }
    return result;
}