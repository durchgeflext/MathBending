#pragma once
#include <cstdint>

struct Integer128 {
    private:
    int64_t hi;
    uint64_t lo;

    public:
    Integer128() : hi(0) , lo(0) {}
    Integer128(const Integer128 &integer128) = default;
    Integer128(Integer128 &&integer128) = default;

    explicit Integer128(const int64_t value) {
        hi = (value < 0) ? int64_t{-1} : int64_t{0};
        lo = static_cast<uint64_t>(value);
    }

    //Shift operators

    constexpr Integer128 operator << (const uint64_t right) const {
        Integer128 tmp{};
        const uint64_t loMask = ~(~uint64_t{0} >> right); //Highest 'right' bits are 1, the rest is 0
        const uint64_t carry = (lo & loMask) >> (64 - right);

        tmp.hi = hi << right;
        tmp.hi |= static_cast<int64_t>(carry);

        tmp.lo = lo << right;
        return tmp;
    }

    constexpr Integer128 operator >> (const uint64_t right) const {
        Integer128 tmp{};
        const uint64_t hiMask = (uint64_t{0} << (right + 1)) - 1; //Lowest 'right' bits are 1, the rest is 0
        const uint64_t carry = (hi & hiMask) << (64 - right);

        tmp.lo = lo >> right;
        tmp.lo |= carry;

        tmp.hi = hi >> right;
        return tmp;
    }

    // Logic operators

    constexpr Integer128 operator & (const Integer128& other) const {

    }

    constexpr Integer128 operator | (const Integer128& other) const {

    }

    constexpr Integer128 operator ^ (const Integer128& other) const {

    }

    constexpr Integer128 operator ~ () const {

    }

    // Comparison operator

    constexpr Integer128 operator <=> (const Integer128& other) const {

    }


    // Arithmetic Operators

    constexpr Integer128 operator + (const Integer128& other) const {

    }

    constexpr Integer128 operator - (const Integer128& other) const {

    }

    constexpr Integer128 operator * (const Integer128& other) const {

    }

    constexpr Integer128 operator / (const Integer128& other) const {

    }

    constexpr Integer128 operator ++ () const {

    }

    constexpr Integer128 operator -- () const {

    }

};

struct UnsignedInteger128 {
    private:
    uint64_t hi;
    uint64_t lo;

    public:
    UnsignedInteger128() : hi(0), lo(0) {}
    UnsignedInteger128(const UnsignedInteger128 &integer128) = default;
    UnsignedInteger128(UnsignedInteger128 &&integer128) = default;

    explicit UnsignedInteger128(const uint64_t value) {
        hi = 0;
        lo = value;
    }

    constexpr UnsignedInteger128 operator << (const uint64_t right) const {
        UnsignedInteger128 tmp{};
        const uint64_t loMask = ~(~uint64_t{0} >> right); //Highest 'right' bits are 1, the rest is 0
        const uint64_t carry = (lo & loMask) >> (64 - right);

        tmp.hi = hi << right;
        tmp.hi |= carry;

        tmp.lo = lo << right;
        return tmp;
    }

    constexpr UnsignedInteger128 operator >> (const uint64_t right) const {
        UnsignedInteger128 tmp{};
        const uint64_t hiMask = (uint64_t{0} << (right + 1)) - 1; //Lowest 'right' bits are 1, the rest is 0
        const uint64_t carry = (hi & hiMask) << (64 - right);

        tmp.lo = lo >> right;
        tmp.lo |= carry;

        tmp.hi = hi >> right;
        return tmp;
    }

    // Logic operators

    constexpr UnsignedInteger128 operator & (const UnsignedInteger128& other) const {

    }

    constexpr UnsignedInteger128 operator | (const UnsignedInteger128& other) const {

    }

    constexpr UnsignedInteger128 operator ^ (const UnsignedInteger128& other) const {

    }

    constexpr UnsignedInteger128 operator ~ () const {

    }

    // Comparison operator

    constexpr UnsignedInteger128 operator <=> (const UnsignedInteger128& other) const {

    }


    // Arithmetic Operators

    constexpr UnsignedInteger128 operator + (const UnsignedInteger128& other) const {

    }

    constexpr UnsignedInteger128 operator - (const UnsignedInteger128& other) const {

    }

    constexpr UnsignedInteger128 operator * (const UnsignedInteger128& other) const {

    }

    constexpr UnsignedInteger128 operator / (const UnsignedInteger128& other) const {

    }

    constexpr UnsignedInteger128 operator ++ () const {

    }

    constexpr UnsignedInteger128 operator -- () const {

    }

};


#ifdef __SIZEOF_INT128__
using int128_t = __int128_t;
using uint128_t = __uint128_t;
#else
using int128_t = Integer128;
using uint128_t = UnsignedInteger128;
#endif

