#pragma once

#include <cstdint>

#ifndef __SIZEOF_INT128__

#if defined(_MSC_VER) && defined (_WIN64)
#include <intrin.h>
#pragma intrinsic(_umul128)
#endif

struct Integer128 {
    private:
    int64_t hi;
    uint64_t lo;

    public:
    constexpr Integer128() : hi(0) , lo(0) {}
    constexpr Integer128(const Integer128 &integer128) = default;
    constexpr Integer128(Integer128 &&integer128) = default;

    constexpr Integer128(const int64_t value) {
        hi = (value < 0) ? int64_t{-1} : int64_t{0};
        lo = static_cast<uint64_t>(value);
    }

    constexpr Integer128(const int64_t hi, const uint64_t lo) : hi(hi), lo(lo) {}


    // Copy assignment operator

    constexpr Integer128& operator = (const Integer128& other) = default;


    //Shift operators

    constexpr Integer128 operator << (const uint64_t shift) const {
        Integer128 tmp{};

        if (shift >= 64) {
            tmp.hi = static_cast<int64_t>(lo << (shift - 64));
            tmp.lo = 0;
            return tmp;
        }

        const uint64_t loMask = ~(~uint64_t{0} >> shift); //Highest 'shift' bits are 1, the rest is 0
        const uint64_t carry = (lo & loMask) >> (64 - shift);

        tmp.hi = hi << shift;
        tmp.hi |= static_cast<int64_t>(carry);

        tmp.lo = lo << shift;
        return tmp;
    }

    constexpr Integer128 operator >> (const uint64_t shift) const {
        Integer128 tmp{};

        if (shift >= 64) {
            tmp.lo = hi >> (shift - 64);
            tmp.hi = (hi < 0) ? int64_t{-1} : int64_t{0};
            return tmp;
        }

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

    constexpr Integer128 operator - () const {
        return Integer128{~hi, ~lo} + Integer128{0, 1};
    }

#if defined(_MSC_VER) && defined(_WIN64)
    Integer128 operator * (const Integer128& other) const {
        Integer128 res{0};
        uint64_t carry = 0;
        const uint64_t lo_lo = _umul128(this->lo, other.lo, &carry);

        const uint64_t tmphi1 = this->lo * static_cast<uint64_t>(other.hi);
        const uint64_t tmphi2 = static_cast<uint64_t>(this->hi) * other.lo;

        res.hi = static_cast<int64_t>(tmphi1 + tmphi2 + carry);
        res.lo = lo_lo;
        return res;
    }

#else  // Fallback implementation
    constexpr Integer128 operator * (const Integer128& other) const {
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
#endif

#if defined(_MSC_VER) && defined(_WIN64)
   Integer128 operator / (const Integer128& other) const {
        const bool negX = *this < 0;
        const bool negY = other < 0;
        const int64_t sign = (negX == negY) ? 1 : -1;

        //Take absolute values
        const Integer128 x = negX ? *this * Integer128{-1} : *this;
        const Integer128 y = negY ? other * Integer128{-1} : other;

        Integer128 res{0};
        uint64_t remainder = 0;
        unsigned long msbIDX;

        if (!_BitScanReverse64(&msbIDX, y.hi)) {
            remainder = static_cast<uint64_t>(x.hi) % y.lo;
            res.hi = static_cast<int64_t>(static_cast<uint64_t>(x.hi) / y.lo);
            res.lo = _udiv128(remainder, x.lo, y.lo, &remainder);
            return res * Integer128{sign};
        }

        const uint64_t xHi = static_cast<uint64_t>(x.hi);
        const uint64_t xLo = x.lo;
        const uint64_t yHi = static_cast<uint64_t>(y.hi);
        const uint64_t yLo = y.lo;

        const char shift = static_cast<char>(msbIDX + 1);

        uint64_t xHatHi;
        uint64_t xHatLo;
        if (shift == 64) {
            xHatHi = 0;
            xHatLo = xHi;
        }
        else {
            xHatLo = __shiftright128(xLo, xHi, shift);
            xHatHi = xHi >> shift;
        }

        const uint64_t yHatLo = __shiftleft128(yLo, yHi, static_cast<unsigned char>(64 - shift));

        uint64_t q = _udiv128(xHatHi, xHatLo, yHatLo, &remainder);
        q = (q >= 2) ? q - 2 : 0;

        // r = x - q*y.  Since q*y <= x, nothing overflows.
        uint64_t pHi;
        const uint64_t pLo = _umul128(q, yLo, &pHi);
        pHi += q * yHi;
        uint64_t rLo = xLo - pLo;
        uint64_t rHi = xHi - pHi - (xLo < pLo);

        while (rHi > yHi || (rHi == yHi && rLo >= yLo)) {
            ++q;
            const uint64_t nLo = rLo - yLo;
            rHi = rHi - yHi - (rLo < yLo);
            rLo = nLo;
        }

        res.hi = 0;
        res.lo = q;
        return res * Integer128{sign};
    }
#else         // Fallback implementation
    constexpr Integer128 operator / (const Integer128& other) const {

        // result is negative if signs differ
        const bool dividendNegative = hi < 0;
        const bool divisorNegative = other.hi < 0;
        const bool resultNegative = dividendNegative != divisorNegative;

        // Work with absolute values
        const Integer128 dividend = dividendNegative ? -*this : *this;
        const Integer128 divisor = divisorNegative ? -other : other;

        Integer128 quotient{0};
        Integer128 remainder{0};
        for (int i = 127; i >= 0; --i) {
            remainder = (remainder << 1) | Integer128{(dividend >> i) & Integer128{1}};
            if (remainder >= divisor) {
                remainder = remainder - divisor;
                quotient = quotient | (Integer128{1} << i);
            }
        }

        return resultNegative ? -quotient : quotient;
    }
#endif

    constexpr Integer128 operator % (const Integer128& other) const {
        const Integer128 res = *this / other;
        return *this - (res * other);
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


    // Conversion Operators

    explicit constexpr operator int64_t() const {
        return static_cast<int64_t>(lo);
    }
};

struct UnsignedInteger128 {
    private:
    uint64_t hi;
    uint64_t lo;

    public:
    constexpr UnsignedInteger128() : hi(0), lo(0) {}
    constexpr UnsignedInteger128(const UnsignedInteger128 &integer128) = default;
    constexpr UnsignedInteger128(UnsignedInteger128 &&integer128) = default;

    constexpr UnsignedInteger128(const uint64_t value) {
        hi = 0;
        lo = value;
    }

    constexpr UnsignedInteger128(const uint64_t hi, const uint64_t lo) : hi(hi), lo(lo) {}


    // Copy assignment operator

    constexpr UnsignedInteger128& operator = (const UnsignedInteger128& other) = default;


    // Shift operators

    constexpr UnsignedInteger128 operator << (const uint64_t shift) const {
        UnsignedInteger128 tmp;

        if (shift >= 64) {
            tmp.hi = lo << (shift - 64);
            tmp.lo = 0;
            return tmp;
        }

        const uint64_t loMask = ~(~uint64_t{0} >> shift); //Highest 'shift' bits are 1, the rest is 0
        const uint64_t carry = (lo & loMask) >> (64 - shift);

        tmp.hi = hi << shift;
        tmp.hi |= carry;

        tmp.lo = lo << shift;
        return tmp;
    }

    constexpr UnsignedInteger128 operator >> (const uint64_t shift) const {
        UnsignedInteger128 tmp{};

        if (shift >= 64) {
            tmp.lo = hi >> (shift - 64);
            tmp.hi = 0;
            return tmp;
        }

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
        if (hi > other.hi) return false;
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

#if defined(_MSC_VER) && defined(_WIN64)
    UnsignedInteger128 operator * (const UnsignedInteger128& other) const {
        UnsignedInteger128 res{0};
        uint64_t carry = 0;
        const uint64_t lo_lo = _umul128(this->lo, other.lo, &carry);

        res.hi = carry + this->hi * other.lo + this->lo * other.hi;
        res.lo = lo_lo;

        return res;
    }
#else  //Fallback implementation
    constexpr UnsignedInteger128 operator * (const UnsignedInteger128& other) const {
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

#endif

#if defined(_MSC_VER) && defined(_WIN64)
    UnsignedInteger128 operator / (const UnsignedInteger128& other) const {
        UnsignedInteger128 res{0};
        uint64_t remainder = 0;
        unsigned long msbIDX;

        if (!_BitScanReverse64(&msbIDX, other.hi)) {
            remainder = this->hi % other.lo;
            res.hi = this->hi / other.lo;
            res.lo = _udiv128(remainder, this->lo, other.lo, &remainder);
            return res;
        }

        const uint64_t shift = msbIDX + 1;
        const UnsignedInteger128 xHat = *this >> shift;
        const uint64_t           yHat = (other >> shift).lo;
        uint64_t                 qHat = _udiv128(xHat.hi, xHat.lo, yHat, &remainder);

        qHat = (qHat >= 2) ? qHat - 2 : 0;
        res = UnsignedInteger128{qHat};

        UnsignedInteger128 rem = *this - res * other;
        while (rem >= other) {
            ++res;
            rem = rem - other;
        }
        return res;
    }
#else  //Fallback implementation
    constexpr UnsignedInteger128 operator / (const UnsignedInteger128& other) const {
        // Fallback implementation
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
#endif

    UnsignedInteger128 operator % (const UnsignedInteger128& other) const {
        const UnsignedInteger128 div = *this / other;
        return *this - (div * other);
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


    // Conversion Operators

    explicit constexpr operator uint64_t() const {
        return lo;
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