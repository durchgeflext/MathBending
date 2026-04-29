#pragma once

#include <array>
#include <cstddef>

namespace MathBending {
    namespace detail {
        template<typename T, size_t _N, size_t _M>
        class Matrix {
            std::array<std::array<T, _M>, _N> data;
        };
    }

    template<typename T, size_t _N, size_t _M>
    using Matrix = detail::Matrix<T, _N, _M>;
}
