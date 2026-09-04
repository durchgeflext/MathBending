#pragma once

#include <cmath>

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

            explicit Matrix(const std::initializer_list<T>& values) {
                static_assert(values.size() == 3);
                x = values[0];
                y = values[1];
                z = values[2];
            }

            explicit Matrix(const Vec2<T>& values) : x(values.x), y(values.y), z(0) {}

            //Assignment operator
            Matrix& operator=(const Matrix& other) {
                data[0] = other.data[0];
                data[1] = other.data[1];
                data[2] = other.data[2];
                return *this;
            }

            //Arithmetic
            //Add
            Matrix operator + (const Matrix& other) const {
                return {x + other.x, y + other.y, z + other.z};
            }

            //Sub
            Matrix operator - (const Matrix& other) const {
                return {x - other.x, y - other.y, z - other.z};
            }

            //scalarMul
            Matrix operator * (const T& scalar) const {
                return {scalar * x, scalar * y, scalar * z};
            }

            T dot(const Matrix& other) const {
                return {x * other.x + y * other.y + z * other.z};
            }

            Matrix cross(const Matrix& other) const {
                return {y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x};
            }

            //Access
            T operator[](const size_t pos) const {
                return data[pos];
            }

            T& operator[](const size_t pos) {
                return data[pos];
            }

            // Other functions
            T length() const {
                return std::sqrt(x* x + y * y + z * z);
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
    using Vec3 = detail::Matrix<T, 3, 1>;

    template<typename T>
    static T length(const Vec3<T>& vec) {
        return vec.length();
    }

    template<typename T, size_t N_>
    static Vec3<T> normalize(const Vec3<T>& vec) {
        return vec.get_normalized();
    }
}