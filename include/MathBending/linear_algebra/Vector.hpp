#pragma once

#include <cmath>
#include <cstddef>

#include "Matrix.hpp"

namespace MathBending {
    namespace detail {
        template<typename T, size_t N_>
        struct Matrix<T, N_, 1> {
            std::array<T, N_> data;

            explicit Matrix() = default;
            explicit Matrix(Matrix& mat) = default;
            explicit Matrix(Matrix&& mat) = default;
            ~Matrix() = default;

            explicit Matrix(T value) {
                for (size_t i = 0;i < N_; i++) {
                    data[i] = value;
                }
            }

            explicit Matrix(T values...) {
                static_assert(values <= N_);
                std::va_list vals;
                va_start(vals, values);
                for (size_t i = 0; i < values; i++) {
                    data[i] = va_arg(vals, T);
                }
                va_end(vals);
            }

            explicit Matrix(const std::initializer_list<T>& values) {
                static_assert(values == N_);
                for (size_t i = 0; i < N_; i++) {
                    data[i] = values[i];
                }
            }

            //Arithmetic
            //Add
            Matrix operator + (const Matrix& other) const {
                Matrix res;
                for (size_t i = 0; i < N_; i++) {
                    res[i] = data[i] + other.data[i];
                }
                return res;
            }

            //Sub
            Matrix operator - (const Matrix& other) const {
                Matrix res;
                for (size_t i = 0; i < N_; i++) {
                    res[i] = data[i] - other.data[i];
                }
                return res;
            }

            //scalarMul
            Matrix operator * (const T& scalar) const {
                Matrix res;
                for (size_t i = 0; i < N_; i++) {
                    res[i] = data[i] * scalar;
                }
                return res;
            }

            //dot
            T dot(const Matrix& other) const {
                T sum = 0;
                for (size_t i = 0; i < N_; i++) {
                    sum += data[i] * other.data[i];
                }
                return sum;
            }

            //Access
            T operator [](const size_t pos) const {
                return data[pos];
            }

            T& operator[](const size_t pos) {
                return data[pos];
            }

            // Other functions
            T length() const {
                T sum{0};
                for (auto value : data) {
                    sum += value * value;
                }
                return std::sqrt(sum);
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

    template<typename T, size_t N_>
    using Vec = detail::Matrix<T,N_,1>;

    template<typename T, size_t N_>
    static T length(const Vec<T, N_>& vec) {
        return vec.length();
    }

    template<typename T, size_t N_>
    static Vec<T, N_> normalize(const Vec<T, N_>& vec) {
        return vec.get_normalized();
    }
}
