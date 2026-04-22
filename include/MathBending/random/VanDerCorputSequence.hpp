#pragma once

#include <cstddef>

#include "MathBending/concepts/ScalarTypes.hpp"

namespace MathBending {
    template <FLT_TYPE flt, size_t base>
    class VanDerCorputSequence {
        size_t start = 0;

        struct state {
            flt nom = 0.0;
            flt denom = static_cast<flt>(base);
        };

        public:
        VanDerCorputSequence() = default;
        explicit VanDerCorputSequence(const size_t start) : start(start) {}

        explicit VanDerCorputSequence(const VanDerCorputSequence &sequence) = default;

        explicit VanDerCorputSequence(VanDerCorputSequence &&sequence) = default;

        flt operator() () {
            return 0.0;
        }

    };
}
