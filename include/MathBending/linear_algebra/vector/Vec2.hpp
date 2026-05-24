#pragma once

#include "MathBending/linear_algebra/Matrix.hpp"

namespace MathBending {
    namespace detail {
        template<typename T>
        struct Matrix<T, 2, 1> {
            union {
                std::array<T, 2> data;
                struct {T x, y;};
                struct {T u, v;};
            };

            explicit Matrix() = default;
            explicit Matrix(Matrix& mat) = default;
            explicit Matrix(Matrix&& mat) = default;
            ~Matrix() = default;

            explicit Matrix(T value) : data{value,value} {}

            Matrix(T x, T y) : x(x), y(y) {}

            Matrix(const std::initializer_list<T>& values) {
                static_assert(values.size() == 2);
                x = values[0];
                y = values[1];
            }

            //Assignment operator
            Matrix& operator=(const Matrix& other) {
                data[0] = other.data[0];
                data[1] = other.data[1];
                return *this;
            }


            //Arithmetic
            //Add
            Matrix operator + (const Matrix& other) const {
                return {x + other.x, y + other.y};
            }

            //Sub
            Matrix operator - (const Matrix& other) const {
                return {x - other.x, y - other.y};
            }

            //scalarMul
            Matrix operator * (const T& scalar) const {
                return {scalar * x, scalar * y};
            }

            //dot
            T dot(const Matrix& other) const {
                return {x * other.x + y * other.y};
            }

            //TODO: Dummy for cross

            //Access
            T operator[](const size_t pos) const {
                return data[pos];
            }

            T& operator[](const size_t pos) {
                return data[pos];
            }
        };
    }
    template<typename T>
    using Vec2 = detail::Matrix<T, 2, 1>;
}