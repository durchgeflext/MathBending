#pragma once
#include <compare>
#include <cstdint>

#ifndef __SIZEOF_INT128__
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

    explicit Integer128(const int64_t hi, const uint64_t lo) : hi(hi), lo(lo) {}

    //Shift operators

    constexpr Integer128 operator << (const uint64_t shift) const {
        Integer128 tmp{};
        const uint64_t loMask = ~(~uint64_t{0} >> shift); //Highest 'shift' bits are 1, the rest is 0
        const uint64_t carry = (lo & loMask) >> (64 - shift);

        tmp.hi = hi << shift;
        tmp.hi |= static_cast<int64_t>(carry);

        tmp.lo = lo << shift;
        return tmp;
    }

    constexpr Integer128 operator >> (const uint64_t shift) const {
        Integer128 tmp{};
        const uint64_t hiMask = (uint64_t{1} << shift) - 1; //Lowest 'shift' bits are 1, the rest is 0
        const uint64_t carry = (hi & hiMask) << (64 - shift);

        tmp.lo = lo >> shift;
        tmp.lo |= carry;

        tmp.hi = hi >> shift;
        return tmp;
    }

    // Logic operators

    constexpr Integer128 operator & (const Integer128& other) const {
        return Integer128{hi & other.hi, lo & other.lo};
    }

    constexpr Integer128 operator | (const Integer128& other) const {
        return Integer128{hi | other.hi, lo | other.lo};
    }

    constexpr Integer128 operator ^ (const Integer128& other) const {
        return Integer128{hi ^ other.hi, lo ^ other.lo};
    }

    constexpr Integer128 operator ~ () const {
        return Integer128{~hi, ~lo};
    }


    // Comparison operator

    constexpr bool operator == (const Integer128& other) const {
        if (hi != other.hi) return false;
        return lo == other.lo;
    }

    constexpr bool operator != (const Integer128& other) const {
        return !operator==(other);
    }

    constexpr bool operator < (const Integer128& other) const {
        if (hi < other.hi) return true;
        if (hi > other.hi) return false;
        return lo < other.lo;
    }

    constexpr bool operator > (const Integer128& other) const {
        if (hi > other.hi) return true;
        if (hi < other.hi) return false;
        return lo > other.lo;
    }

    constexpr bool operator <= (const Integer128& other) const {
        return (*this < other) || (*this == other);
    }

    constexpr bool operator >= (const Integer128& other) const {
        return (*this > other) || (*this == other);
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

    constexpr Integer128& operator ++ () {
        if (++lo == 0) ++hi;
        return *this;
    }

    constexpr Integer128 operator ++ (int) {
        const Integer128 tmp = *this;
        ++*this;
        return tmp;
    }


    constexpr Integer128& operator -- () {
        if (lo-- == 0) --hi;
        return *this;
    }

    constexpr Integer128 operator -- (int) {
        const Integer128 tmp = *this;
        --*this;
        return tmp;
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

    explicit UnsignedInteger128(const uint64_t hi, const uint64_t lo) : hi(hi), lo(lo) {}

    constexpr UnsignedInteger128 operator << (const uint64_t shift) const {
        UnsignedInteger128 tmp{};
        const uint64_t loMask = ~(~uint64_t{0} >> shift); //Highest 'shift' bits are 1, the rest is 0
        const uint64_t carry = (lo & loMask) >> (64 - shift);

        tmp.hi = hi << shift;
        tmp.hi |= carry;

        tmp.lo = lo << shift;
        return tmp;
    }

    constexpr UnsignedInteger128 operator >> (const uint64_t shift) const {
        UnsignedInteger128 tmp{};
        const uint64_t hiMask = (uint64_t{1} << shift) - 1; //Lowest 'shift' bits are 1, the rest is 0
        const uint64_t carry = (hi & hiMask) << (64 - shift);

        tmp.lo = lo >> shift;
        tmp.lo |= carry;

        tmp.hi = hi >> shift;
        return tmp;
    }


    // Logic operators

    constexpr UnsignedInteger128 operator & (const UnsignedInteger128& other) const {
        return UnsignedInteger128{hi & other.hi, lo & other.lo};
    }

    constexpr UnsignedInteger128 operator | (const UnsignedInteger128& other) const {
        return UnsignedInteger128{hi | other.hi, lo | other.lo};
    }

    constexpr UnsignedInteger128 operator ^ (const UnsignedInteger128& other) const {
        return UnsignedInteger128{hi ^ other.hi, lo ^ other.lo};
    }

    constexpr UnsignedInteger128 operator ~ () const {
        return UnsignedInteger128{~hi, ~lo};
    }


    // Comparison operator

    constexpr bool operator == (const UnsignedInteger128& other) const {
        if (hi != other.hi) return false;
        return lo == other.lo;
    }

    constexpr bool operator != (const UnsignedInteger128& other) const {
        return !operator==(other);
    }

    constexpr bool operator < (const UnsignedInteger128& other) const {
        if (hi < other.hi) return true;
        if (hi > other.hi) return true;
        return lo < other.lo;
    }

    constexpr bool operator > (const UnsignedInteger128& other) const {
        if (hi > other.hi) return true;
        if (hi < other.hi) return false;
        return lo > other.lo;
    }

    constexpr bool operator <= (const UnsignedInteger128& other) const {
        return (*this < other) || (*this == other);
    }

    constexpr bool operator >= (const UnsignedInteger128& other) const {
        return (*this > other) || (*this == other);
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

    constexpr UnsignedInteger128& operator ++ () {
        if (++lo == 0) ++hi;
        return *this;
    }

    constexpr UnsignedInteger128 operator ++ (int) {
        const UnsignedInteger128 tmp = *this;
        ++*this;
        return tmp;
    }


    constexpr UnsignedInteger128& operator -- () {
        if (lo-- == 0) --hi;
        return *this;
    }

    constexpr UnsignedInteger128 operator -- (int) {
        const UnsignedInteger128 tmp = *this;
        --*this;
        return tmp;
    }
};
#endif


#ifdef __SIZEOF_INT128__
using int128_t = __int128_t;
using uint128_t = __uint128_t;
#else
using int128_t = Integer128;
using uint128_t = UnsignedInteger128;
#endif

