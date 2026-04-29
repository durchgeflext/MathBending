#pragma once

#include <cstddef>

#include "matrix.hpp"

namespace MathBending {
    namespace detail {
        template<typename T, size_t _N>
        class Matrix<T, _N, 1> {

        };
    }

    template<typename T, size_t _N>
    using Vec = detail::Matrix<T,_N,1>;
}
