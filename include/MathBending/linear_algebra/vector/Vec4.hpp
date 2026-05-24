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

            explicit Matrix(const std::initializer_list<T>& values) {
                static_assert(values.size() == 4);
                x = values[0];
                y = values[1];
                z = values[2];
                w = values[3];
            }

            explicit Matrix(const Vec2<T>& values) : x(values.x), y(values.y), z(0), w(0) {}
            explicit Matrix(const Vec3<T>& values) : x(values.x), y(values,y), z(values.z), w(0) {}

            //Assignment operator
            Matrix& operator=(const Matrix& other) {
                data[0] = other.data[0];
                data[1] = other.data[1];
                data[2] = other.data[2];
                data[3] = other.data[3];
                return *this;
            }

            //Arithmetic
            //Add
            Matrix operator + (const Matrix& other) const {
                return {x + other.x, y + other.y, z + other.z, w + other.w};
            }

            //Sub
            Matrix operator - (const Matrix& other) const {
                return {x - other.x, y - other.y, z - other.z, w - other.w};
            }

            //scalarMul
            Matrix operator * (const T& scalar) const {
                return {scalar * x, scalar * y, scalar * z, scalar * w};
            }

            //dot
            T dot(const Matrix& other) const {
                return {x * other.x + y * other.y + z * other.z + w * other.w};
            }

            //TODO: cross

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
    using Vec4 = detail::Matrix<T, 4, 1>;
}