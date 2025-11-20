#pragma once
#include <concepts>
#include <cstdint>

template<typename T>
concept U_INT_TYPE = std::is_same_v<T, uint32_t> || std::is_same_v<T, uint64_t>;