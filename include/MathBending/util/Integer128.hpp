#pragma once
#include <cstdint>

struct Integer128 {
    private:
    uint64_t hi;
    uint64_t lo;

    static constexpr uint64_t NEGATIVE_MASK = uint64_t{1} << 63;
    static constexpr uint64_t INIT_MASK_64 = ~(uint64_t{1} << 63);

    public:
    Integer128() = default;
    Integer128(const Integer128 &integer128) = default;
    Integer128(Integer128 &&integer128) = default;

    explicit Integer128(const int64_t value) {
        hi = value & NEGATIVE_MASK;
        lo = value & INIT_MASK_64;
    }
};

struct UnsignedInteger128 {
    private:
    uint64_t hi;
    uint64_t lo;

    public:
    UnsignedInteger128() = default;
    UnsignedInteger128(const UnsignedInteger128 &integer128) = default;
    UnsignedInteger128(UnsignedInteger128 &&integer128) = default;

    explicit UnsignedInteger128(const uint64_t value) {
        hi = 0;
        lo = value;
    }

};


#ifdef __SIZEOF_INT128__
using int128_t = __int128_t;
using uint128_t = __uint128_t;
#else
using int128_t = Integer128;
using uint128_t = UnsignedInteger128;
#endif

