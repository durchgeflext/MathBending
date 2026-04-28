#pragma once

#include <cstddef>

#include "MathBending/concepts/ScalarTypes.hpp"

namespace MathBending {
    template <FLT_TYPE flt, size_t base>
    class VanDerCorputSequence {
        size_t start = 0;

        struct State {
            uint64_t nom = 0.0;
            uint64_t denom = static_cast<flt>(base);
        };
        State state;

        public:
        VanDerCorputSequence() = default;
        explicit VanDerCorputSequence(const size_t start) : start(start) {
            for (size_t i = 0; i < start; i++) {
                this();
            }
        }

        explicit VanDerCorputSequence(const VanDerCorputSequence &sequence) = default;

        explicit VanDerCorputSequence(VanDerCorputSequence &&sequence) = default;

        flt operator() () {
            //TODO: Fix this
            flt res = static_cast<flt>(state.nom) / static_cast<flt>(state.denom);
            ++state.nom;
            if (state.nom % base == 0) {
                state.nom /= base;
                state.denom *= base;
            }
            return res;
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
}
