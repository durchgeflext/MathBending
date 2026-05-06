#pragma once

#include "MathBending/linear_algebra/Matrix.hpp"

namespace MathBending {
    namespace detail {
        template<typename T>
        struct Matrix<T, 3, 1> {
            union {
                std::array<T, 3> data;
                struct {T x, y, z;};
                struct {T r, g, b;};
            };

            explicit Matrix() = default;
            explicit Matrix(Matrix& mat) = default;
            explicit Matrix(Matrix&& mat) = default;
            ~Matrix() = default;

            explicit Matrix(T value) : data{value, value, value} {}

            explicit Matrix(T x, T y) : x(x), y(y), z(0) {}
            explicit Matrix(T x, T y, T z) : x(x), y(y), z(z) {}
        };
    }
    template<typename T>
    using Vec3 = detail::Matrix<T, 3, 1>;
}