#pragma once

#include <cstddef>
#include <cstring>
#include <emmintrin.h>
#include "MathBending/concepts/ScalarTypes.hpp"
#include "MathBending/platform/sse2.hpp"
#include "MathBending/util/Integer128.hpp"

template<U_INT_TYPE word_t, U_INT_TYPE sgmnt_t>
static constexpr word_t sgmnt_bit_shift_l_impl(const word_t word, const size_t shift, scalar_tag) {
    if constexpr (sizeof(word_t) == sizeof(sgmnt_t)) {
        return word << shift;
    } else {
        sgmnt_t sgmnt_mask = static_cast<sgmnt_t>(~0) << shift;
        word_t mask = 0;
        for (size_t i = 0; i < sizeof(word_t) / sizeof(sgmnt_t); i++) {
            mask <<= sizeof(sgmnt_t) * 8;
            mask |= sgmnt_mask;
        }
        return (word << shift) & mask;
    }
}

template<U_INT_TYPE word_t, U_INT_TYPE sgmnt_t>
static constexpr word_t sgmnt_bit_shift_l_impl(const word_t word, const size_t shift, sse2_epi8_tag) {
    word_t result = 0;
    __m128i a;
    std::memcpy(&a, &word, sizeof(word_t));
    const __m128i mask = _mm_set1_epi8(static_cast<char>(0xff << shift));
    const __m128i r = _mm_and_si128(_mm_slli_epi16(a, static_cast<int>(shift)), mask);
    std::memcpy(&result, &r, sizeof(word_t));
    return result;
}


template<U_INT_TYPE word_t, U_INT_TYPE sgmnt_t>
static constexpr word_t sgmnt_bit_shift_l_impl(const word_t word, const size_t shift, sse2_epi16_tag) {
    word_t result = 0;
    __m128i a;
    std::memcpy(&a, &word, sizeof(word_t));
    const __m128i r = _mm_slli_epi16(a,static_cast<int>(shift));
    std::memcpy(&result, &r, sizeof(word_t));
    return result;
}


template<U_INT_TYPE word_t, U_INT_TYPE sgmnt_t>
static constexpr word_t sgmnt_bit_shift_l_impl(const word_t word, const size_t shift, sse2_epi32_tag) {
    word_t result = 0;
    __m128i a;
    std::memcpy(&a, &word, sizeof(word_t));
    const __m128i r = _mm_slli_epi32(a,static_cast<int>(shift));
    std::memcpy(&result, &r, sizeof(word_t));
    return result;
}


template<U_INT_TYPE word_t, U_INT_TYPE sgmnt_t>
static constexpr word_t sgmnt_bit_shift_l_impl(const word_t word, const size_t shift, sse2_epi64_tag) {
    word_t result = 0;
    __m128i a;
    std::memcpy(&a, &word, sizeof(word_t));
    const __m128i r = _mm_slli_epi64(a, static_cast<int>(shift));
    std::memcpy(&result, &r, sizeof(word_t));
    return result;
}

template <U_INT_TYPE word_t,U_INT_TYPE sgmnt_t>
static constexpr word_t sgmnt_bit_shift_l_impl(const word_t word, const size_t shift, sse2_epi128_tag) {
    return word << shift;
}

template<U_INT_TYPE word_t, U_INT_TYPE sgmnt_t>
static constexpr word_t sgmnt_bit_shift_l(const word_t word, const size_t shift) {
    static_assert(sizeof(sgmnt_t) <= sizeof(word_t), "The segment size cannot be greater than the word size");

    return sgmnt_bit_shift_l_impl<word_t, sgmnt_t>(word, shift, shift_tag<word_t, sgmnt_t>());
}



template <U_INT_TYPE word_t, U_INT_TYPE sgmnt_t>
static constexpr word_t sgmnt_bit_shift_r_impl(const word_t word, const size_t shift, scalar_tag) {
    if constexpr (sizeof(word) == sizeof(sgmnt_t)) {
        return word >> shift;
    } else {
        sgmnt_t sgmnt_mask = static_cast<sgmnt_t>(~0) >> shift;
        word_t mask= 0;
        for (size_t i = 0; i < sizeof(word_t) / sizeof(sgmnt_t); i++) {
            mask <<= sizeof(sgmnt_t) * 8;
            mask |= sgmnt_mask;
        }
        return (word >> shift) & mask;
    }
}

template<U_INT_TYPE word_t, U_INT_TYPE sgmnt_t>
static constexpr word_t sgmnt_bit_shift_r_impl(const word_t word, const size_t shift, sse2_epi8_tag) {
    word_t result = 0;
    __m128i a;
    std::memcpy(&a, &word, sizeof(word_t));
    const __m128i mask = _mm_set1_epi8(static_cast<char>(0xff >> shift));
    const __m128i r = _mm_and_si128(_mm_srli_epi16(a, static_cast<int>(shift)), mask);
    std::memcpy(&result, &r, sizeof(word_t));
    return result;
}

template<U_INT_TYPE word_t, U_INT_TYPE sgmnt_t>
static constexpr word_t sgmnt_bit_shift_r_impl(const word_t word, const size_t shift, sse2_epi16_tag) {
    word_t result = 0;
    __m128i a;
    std::memcpy(&a, &word, sizeof(word_t));
    const __m128i r = _mm_srli_epi16(a,static_cast<int>(shift));
    std::memcpy(&result, &r, sizeof(word_t));
    return result;
}

template<U_INT_TYPE word_t, U_INT_TYPE sgmnt_t>
static constexpr word_t sgmnt_bit_shift_r_impl(const word_t word, const size_t shift, sse2_epi32_tag) {
    word_t result = 0;
    __m128i a;
    std::memcpy(&a, &word, sizeof(word_t));
    const __m128i r = _mm_srli_epi32(a,static_cast<int>(shift));
    std::memcpy(&result, &r, sizeof(word_t));
    return result;
}

template<U_INT_TYPE word_t, U_INT_TYPE sgmnt_t>
static constexpr word_t sgmnt_bit_shift_r_impl(const word_t word, const size_t shift, sse2_epi64_tag) {
    word_t result = 0;
    __m128i a;
    std::memcpy(&a, &word, sizeof(word_t));
    const __m128i r = _mm_srli_epi64(a,static_cast<int>(shift));
    std::memcpy(&result, &r, sizeof(word_t));
    return result;
}

template <U_INT_TYPE word_t,U_INT_TYPE sgmnt_t>
static constexpr word_t sgmnt_bit_shift_r_impl(const word_t word, const size_t shift, sse2_epi128_tag) {
    return word >> shift;
}

template<U_INT_TYPE word_t, U_INT_TYPE sgmnt_t>
static constexpr word_t sgmnt_bit_shift_r(const word_t word, const size_t shift) {
    static_assert(sizeof(sgmnt_t) <= sizeof(word_t), "The segment size cannot be greater than the word size");

    return sgmnt_bit_shift_r_impl<word_t,sgmnt_t>(word, shift, shift_tag<word_t, sgmnt_t>());
}