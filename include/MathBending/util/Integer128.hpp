#pragma once

#include <cstdint>

#ifdef __SIZEOF_INT128__
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


    // Copy assignment operator

    constexpr Integer128& operator = (const Integer128& other) = default;


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
        Integer128 res{0};
        res.lo = this->lo + other.lo;
        const uint64_t carry = (res.lo < this->lo) ? 1 : 0;
        res.hi = this->hi + other.hi + static_cast<int64_t>(carry);
        return res;
    }

    constexpr Integer128 operator - (const Integer128& other) const {
        Integer128 res{0};
        const uint64_t borrow = (this->lo < other.lo) ? 1 : 0;
        res.lo = this->lo - other.lo;
        res.hi = this->hi - other.hi - static_cast<int64_t>(borrow);
        return res;
    }

    constexpr Integer128 operator * (const Integer128& other) const {
        // Really slow fallback implementation
        Integer128 res{0};
        for (uint64_t i = 0; i < 64; ++i) {
            if ((other.lo & (uint64_t{1} << i)) != 0) {
                res = res + (*this << i);
            }
            if ((other.hi & (uint64_t{1} << i)) != 0) {
                res = res + (*this << (i + 64));
            }
        }
        return res;
    }

    constexpr Integer128 operator / (const Integer128& other) const {
        // Really slow fallback implementation
        const Integer128 dividend = *this;
        const Integer128 divisor = other;
        Integer128 quotient{0};
        Integer128 remainder{0};
        for (int i = 127; i >= 0; --i) {
            remainder = (remainder << 1) | Integer128{(dividend >> i) & Integer128{1}};
            if (remainder >= divisor) {
                remainder = remainder - divisor;
                quotient = quotient | (Integer128{1} << i);
            }
        }
        return quotient;
    }

    constexpr Integer128 operator % (const Integer128& other) const {
        // Really slow fallback implementation
        const Integer128 dividend = *this;
        const Integer128 divisor = other;
        Integer128 quotient{0};
        Integer128 remainder{0};
        for (int i = 127; i >= 0; --i) {
            remainder = (remainder << 1) | Integer128{(dividend >> i) & Integer128{1}};
            if (remainder >= divisor) {
                remainder = remainder - divisor;
                quotient = quotient | (Integer128{1} << i);
            }
        }
        return remainder;
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


    // Copy assignment operator

    constexpr UnsignedInteger128& operator = (const UnsignedInteger128& other) = default;


    // Shift operators

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
        UnsignedInteger128 res{0};
        res.lo = this->lo + other.lo;
        const uint64_t carry = (res.lo < this->lo) ? 1 : 0;
        res.hi = this->hi + other.hi + carry;
        return res;
    }

    constexpr UnsignedInteger128 operator - (const UnsignedInteger128& other) const {
        UnsignedInteger128 res{0};
        const uint64_t borrow = (this->lo < other.lo) ? 1 : 0;
        res.lo = this->lo - other.lo;
        res.hi = this->hi - other.hi - static_cast<int64_t>(borrow);
        return res;
    }

    constexpr UnsignedInteger128 operator * (const UnsignedInteger128& other) const {

        //Really slow fallback implementation
        UnsignedInteger128 res{0};
        for (uint64_t i = 0; i < 64; ++i) {
            if ((other.lo & (uint64_t{1} << i)) != 0) {
                res = res + (*this << i);
            }
            if ((other.hi & (uint64_t{1} << i)) != 0) {
                res = res + (*this << (i + 64));
            }
        }
        return res;
    }

    constexpr UnsignedInteger128 operator / (const UnsignedInteger128& other) const {
        // Really slow fallback implementation
        const UnsignedInteger128 dividend = *this;
        const UnsignedInteger128 divisor = other;
        UnsignedInteger128 quotient{0};
        UnsignedInteger128 remainder{0};
        for (int i = 127; i >= 0; --i) {
            remainder = (remainder << 1) | UnsignedInteger128{(dividend >> i) & UnsignedInteger128{1}};
            if (remainder >= divisor) {
                remainder = remainder - divisor;
                quotient = quotient | (UnsignedInteger128{1} << i);
            }
        }
        return quotient;
    }

    constexpr UnsignedInteger128 operator % (const UnsignedInteger128& other) const {
        // Really slow fallback implementation
        const UnsignedInteger128 dividend = *this;
        const UnsignedInteger128 divisor = other;
        UnsignedInteger128 quotient{0};
        UnsignedInteger128 remainder{0};
        for (int i = 127; i >= 0; --i) {
            remainder = (remainder << 1) | UnsignedInteger128{(dividend >> i) & UnsignedInteger128{1}};
            if (remainder >= divisor) {
                remainder = remainder - divisor;
                quotient = quotient | (UnsignedInteger128{1} << i);
            }
        }
        return remainder;
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