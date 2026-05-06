#pragma once

#include "MathBending/linear_algebra/Matrix.hpp"

namespace MathBending {
    namespace detail {
        template<typename T>
        struct Matrix<T, 4, 1> {
            union {
                std::array<T, 4> data;
                struct {T x, y, z, w;};
                struct {T r, g, b, a;};
            };

            explicit Matrix() = default;
            explicit Matrix(Matrix& mat) = default;
            explicit Matrix(Matrix&& mat) = default;
            ~Matrix() = default;

            explicit Matrix(T value) : data{value, value, value, value} {}

            explicit Matrix(T x, T y) : x(x), y(y), z(0), w(0) {}
            explicit Matrix(T x, T y, T z) : x(x), y(y), z(z), w(0) {}
            explicit Matrix(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
        };
    }
    template<typename T>
    using Vec4 = detail::Matrix<T, 4, 1>;
}