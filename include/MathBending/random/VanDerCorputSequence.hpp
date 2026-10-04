#pragma once

#include <bit>
#include <cstddef>

#include "MathBending/concepts/ScalarTypes.hpp"
#include "MathBending/functions/BitReversal.hpp"

namespace MathBending {
    template <FLT_TYPE flt, size_t base>
    class VanDerCorputSequence {
        size_t iteration = 0;

        public:
        VanDerCorputSequence() = default;
        explicit VanDerCorputSequence(const size_t start) : iteration(start) {
            for (size_t i = 0; i < start; i++) {
                this();
            }
        }

        explicit VanDerCorputSequence(const VanDerCorputSequence &sequence) = default;

        explicit VanDerCorputSequence(VanDerCorputSequence &&sequence) = default;

        flt operator() () {
            return vanDerCorput(iteration++);
        }

        static flt vanDerCorput(uint64_t n) {
            flt result = static_cast<flt>(0);
            flt increment = static_cast<flt>(1)/static_cast<flt>(base);
            while (n > 0) {
                uint64_t lsb = n % base;
                result += static_cast<flt>(lsb) * increment;
                n /= base;
                increment /= base;
            }
            return result;
        }

    };

    template<FLT_TYPE flt>
    class VanDerCorputSequence<flt, 2> {
        size_t iteration = 0;

        public:
        VanDerCorputSequence() = default;
        explicit VanDerCorputSequence(const size_t start) : iteration(start) {
            for (size_t i = 0; i < start; i++) {
                this();
            }
        }

        explicit VanDerCorputSequence(const VanDerCorputSequence &sequence) = default;

        explicit VanDerCorputSequence(VanDerCorputSequence &&sequence) = default;

        flt operator() () {
            return vanDerCorput(iteration++);
        }

        static flt vanDerCorput(const uint64_t n) {
            if constexpr (sizeof(flt) == 4) {
                const uint32_t reversed = reverse_bits_32(n);
                return std::bit_cast<flt>(0x3f800000 | (reversed >> 9)) - 1.f;
            } else {
                const uint64_t reversed = reverse_bits_64(n);
                return std::bit_cast<flt>(0x3ff0000000000000 | (reversed >> 12)) - 1.0;
            }
        }
    };
}
