#pragma once

#include <cstddef>

#include "MathBending/concepts/ScalarTypes.hpp"
#include "MathBending/util/Integer128.hpp"

// ==============================================================================
//            8 bit word segmented shift
// ==============================================================================

template<U_INT_TYPE sgmnt>
static constexpr uint8_t segmnt_bit_shift_l(const uint8_t word, const size_t shift) {
    static_assert(sizeof(sgmnt) == 1, "The segment size cannot be greater than the word size");

    return word << shift;
}

template<U_INT_TYPE sgmnt>
static constexpr uint8_t segmnt_bit_shift_r(const uint8_t word, const size_t shift) {
    static_assert(sizeof(sgmnt) == 1, "The segment size cannot be greater than the word size");

    return word >> shift;
}




// ==============================================================================
//            16 bit word segmented shift
// ==============================================================================

template<U_INT_TYPE sgmnt>
static constexpr uint16_t segmnt_bit_shift_l(const uint64_t word, const size_t shift) {
    static_assert(sizeof(sgmnt) <= 2, "The segment size cannot be greater than the word size");

    if constexpr (sizeof(sgmnt) == sizeof(word)) return word << shift;
    uint16_t result = 0;
    const auto* parts = reinterpret_cast<const sgmnt*>(&word);
    auto* resParts = reinterpret_cast<sgmnt*>(&result);
    for (size_t i = 0; i < sizeof(word)/sizeof(sgmnt); i++) {
        resParts[i] = parts[i] << shift;
    }
    return result;
}

template<U_INT_TYPE sgmnt>
static constexpr uint16_t segmnt_bit_shift_r(const uint64_t word, const size_t shift) {
    static_assert(sizeof(sgmnt) <= 2, "The segment size cannot be greater than the word size");

    if constexpr (sizeof(sgmnt) == sizeof(word)) return word >> shift;
    uint16_t result = 0;
    const auto* parts = reinterpret_cast<const sgmnt*>(&word);
    auto* resParts = reinterpret_cast<sgmnt*>(&result);
    for (size_t i = 0; i < sizeof(word)/sizeof(sgmnt); i++) {
        resParts[i] = parts[i] >> shift;
    }
    return result;
}




// ==============================================================================
//            32 bit word segmented shift
// ==============================================================================

template<U_INT_TYPE sgmnt>
static constexpr uint32_t segmnt_bit_shift_l(const uint64_t word, const size_t shift) {
    static_assert(sizeof(sgmnt) <= 4, "The segment size cannot be greater than the word size");

    if constexpr (sizeof(sgmnt) == sizeof(word)) return word << shift;
    uint32_t result = 0;
    const auto* parts = reinterpret_cast<const sgmnt*>(&word);
    auto* resParts = reinterpret_cast<sgmnt*>(&result);
    for (size_t i = 0; i < sizeof(word)/sizeof(sgmnt); i++) {
        resParts[i] = parts[i] << shift;
    }
    return result;
}

template<U_INT_TYPE sgmnt>
static constexpr uint32_t segmnt_bit_shift_r(const uint64_t word, const size_t shift) {
    static_assert(sizeof(sgmnt) <= 4, "The segment size cannot be greater than the word size");

    if constexpr (sizeof(sgmnt) == sizeof(word)) return word >> shift;
    uint32_t result = 0;
    const auto* parts = reinterpret_cast<const sgmnt*>(&word);
    auto* resParts = reinterpret_cast<sgmnt*>(&result);
    for (size_t i = 0; i < sizeof(word)/sizeof(sgmnt); i++) {
        resParts[i] = parts[i] >> shift;
    }
    return result;
}




// ==============================================================================
//            64 bit word segmented shift
// ==============================================================================

template<U_INT_TYPE sgmnt>
static constexpr uint64_t segmnt_bit_shift_l(const uint64_t word, const size_t shift) {
    static_assert(sizeof(sgmnt) <= 8, "The segment size cannot be greater than the word size");

    if constexpr (sizeof(sgmnt) == sizeof(word)) return word << shift;
    uint64_t result = 0;
    const auto* parts = reinterpret_cast<const sgmnt*>(&word);
    auto* resParts = reinterpret_cast<sgmnt*>(&result);
    for (size_t i = 0; i < sizeof(word)/sizeof(sgmnt); i++) {
        resParts[i] = parts[i] << shift;
    }
    return result;
}

template<U_INT_TYPE sgmnt>
static constexpr uint64_t segmnt_bit_shift_r(const uint64_t word, const size_t shift) {
    static_assert(sizeof(sgmnt) <= 8, "The segment size cannot be greater than the word size");

    if constexpr (sizeof(sgmnt) == sizeof(word)) return word >> shift;
    uint64_t result = 0;
    const auto* parts = reinterpret_cast<const sgmnt*>(&word);
    auto* resParts = reinterpret_cast<sgmnt*>(&result);
    for (size_t i = 0; i < sizeof(word)/sizeof(sgmnt); i++) {
        resParts[i] = parts[i] >> shift;
    }
    return result;
}




// ==============================================================================
//            128 bit word segmented shift
// ==============================================================================

template<U_INT_TYPE sgmnt>
static constexpr uint128_t segmnt_bit_shift_l(const uint128_t word, const size_t shift) {
    static_assert(sizeof(sgmnt) <= 16, "The segment size cannot be greater than the word size");
    
    if constexpr (sizeof(sgmnt) == sizeof(word)) return word << shift;
    uint128_t result = 0;
    const auto* parts = reinterpret_cast<const sgmnt*>(&word);
    auto* resParts = reinterpret_cast<sgmnt*>(&result);
    for (size_t i = 0; i < sizeof(word)/sizeof(sgmnt); i++) {
        resParts[i] = parts[i] << shift;
    }
    return result;
}

template<U_INT_TYPE sgmnt>
static constexpr uint128_t segmnt_bit_shift_r(const uint128_t word, const size_t shift) {
    static_assert(sizeof(sgmnt) <= 16, "The segment size cannot be greater than the word size");
    
    if constexpr (sizeof(sgmnt) == sizeof(word)) return word >> shift;
    uint128_t result = 0;
    const auto* parts = reinterpret_cast<const sgmnt*>(&word);
    auto* resParts = reinterpret_cast<sgmnt*>(&result);
    for (size_t i = 0; i < sizeof(word)/sizeof(sgmnt); i++) {
        resParts[i] = parts[i] >> shift;
    }
    return result;
}