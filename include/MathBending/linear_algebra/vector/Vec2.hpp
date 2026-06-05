#pragma once

#include <cmath>

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

            //"cross" Computes the area of the parallelogram spanned by this and other
            T cross(const Matrix& other) const {
                return x * other.y - y * other.x;
            }

            //Access
            T operator[](const size_t pos) const {
                return data[pos];
            }

            T& operator[](const size_t pos) {
                return data[pos];
            }

            //TODO: Swizzling

            // Other functions
            T length() const {
                return std::sqrt(x* x + y * y);
            }

            Matrix get_normalized() const {
                //TODO: Fast inverse square root?
                return 1. / length() * *this;
            }

            void normalize() {
                *this = 1. / length() * *this;
            }
        };
    }
    template<typename T>
    using Vec2 = detail::Matrix<T, 2, 1>;

    template<typename T>
    static T length(const Vec2<T>& vec) {
        return vec.length();
    }

    template<typename T, size_t N_>
    static Vec2<T> normalize(const Vec2<T>& vec) {
        return vec.get_normalized();
    }
}