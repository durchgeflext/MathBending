#pragma once

#include "MathBending/linear_algebra/matrix.hpp"

namespace MathBending {
    namespace detail {
        template<typename T>
        class Matrix<T, 2, 1> {

        };
    }
    template<typename T>
    using Vec2 = detail::Matrix<T, 2, 1>;
}