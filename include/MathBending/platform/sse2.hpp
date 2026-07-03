#pragma once
#include "MathBending/concepts/ScalarTypes.hpp"
#include "MathBending/platform/platform.hpp"

struct scalar_tag {};

struct sse2_epi8_tag {};
struct sse2_epi16_tag {};
struct sse2_epi32_tag {};
struct sse2_epi64_tag {};
struct sse2_epi128_tag {};

template<U_INT_TYPE word_t, U_INT_TYPE shift_t>
constexpr auto shift_tag() {
#ifdef SSE2_SET
    if constexpr (sizeof(word_t) < 16)  return scalar_tag{};
    else {
        if constexpr (sizeof(shift_t) == 1) return sse2_epi8_tag{};
        if constexpr (sizeof(shift_t) == 2) return sse2_epi16_tag{};
        if constexpr (sizeof(shift_t) == 4) return sse2_epi32_tag{};
        if constexpr (sizeof(shift_t) == 8) return sse2_epi64_tag{};
        if constexpr (sizeof(shift_t) == 16) return sse2_epi128_tag{};
    }
#else
    return scalar_tag{};
#endif
}