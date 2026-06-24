#pragma once

#include <cstddef>
#include <emmintrin.h>
#include <cstring>

#include "MathBending/concepts/ScalarTypes.hpp"
#include "MathBending/util/Integer128.hpp"
#include "MathBending/platform/platform.hpp"

template<U_INT_TYPE word_t, U_INT_TYPE sgmnt_t>
static constexpr word_t sgmnt_bit_shift_l_impl(const word_t word, const size_t shift) {
    word_t result = 0;
    for (size_t i = 0; i < sizeof(word_t) / sizeof(sgmnt_t); i++) {
        sgmnt_t part;
        std::memcpy(&part, reinterpret_cast<char *>(&word) + i * sizeof(sgmnt_t), sizeof(sgmnt_t));
        part <<= shift;
        std::memcpy(reinterpret_cast<char*>(&word) + i * sizeof(sgmnt_t), sizeof(sgmnt_t));
    }
    return result;
}

template<U_INT_TYPE word_t, U_INT_TYPE sgmnt_t>
static constexpr word_t sgmnt_bit_shift_l(const word_t word, const size_t shift) {
    static_assert(sizeof(sgmnt_t) <= sizeof(word_t), "The segment size cannot be greater than the word size");

    if (sizeof(sgmnt_t) == sizeof(word_t)) return word << shift;

    word_t result = 0;
#ifdef SSE2_SET
    //TODO: use tagging for overloading this
    if constexpr (sizeof(word_t) == 16 && sizeof(sgmnt_t) == 4) {
        const __m128i a = _mm_loadu_si128(static_cast<const __m128i *>(&word));
        const __m128i r = _mm_slli_epi32(a, static_cast<int>(shift));
        _mm_storeu_si128(static_cast<__m128i *>(&result), r);
    }
#else
    sgmnt_bit_shift_l_impl<word_t, sgmnt_t>(word, shift);
#endif
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