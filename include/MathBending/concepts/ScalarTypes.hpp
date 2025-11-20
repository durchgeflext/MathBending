#pragma once
#include <concepts>
#include <cstdint>

#include <MathBending/util/Integer128.hpp>

template<typename T>
concept INT_TYPE =
    std::is_same_v<T, int8_t> ||
    std::is_same_v<T, int16_t> ||
    std::is_same_v<T, int32_t> ||
    std::is_same_v<T, int64_t> ||
    std::is_same_v<T, int128_t>;


template<typename T>
concept U_INT_TYPE =
    std::is_same_v<T, uint8_t> ||
    std::is_same_v<T, uint16_t> ||
    std::is_same_v<T, uint32_t> ||
    std::is_same_v<T, uint64_t> ||
    std::is_same_v<T, uint128_t>;
