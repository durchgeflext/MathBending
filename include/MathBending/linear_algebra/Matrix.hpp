#pragma once

#include <array>
#include <cassert>
#include <cstdarg>

namespace MathBending {
    namespace detail {
        template<typename T, size_t N_ = 3, size_t M_ = 3> requires (N_ > 0 && M_ > 0)
        struct Matrix {
            std::array<std::array<T, M_>, N_> data;

            explicit Matrix() = default;
            explicit Matrix(Matrix& mat) = default;
            explicit Matrix(Matrix&& mat) = default;
            ~Matrix() = default;

            explicit Matrix(T value) {
                for (size_t n = 0; n < N_; n++) {
                    for (size_t m = 0; m < M_; m++) {
                        data[n][m] = value;
                    }
                }
            }

            explicit Matrix(const std::initializer_list<T>& values) {
                //TODO: use contract_asset in c++26
                assert(values.size() <= N_ * M_);
                for (size_t v = 0; v < values.size(); v++) {
                    data[v / N_][v % N_] = values.data()[v];
                }
            }

            explicit Matrix(const std::initializer_list<std::initializer_list<T>>& values) {
                //TODO: use contract_asset in c++26
                assert(values.size() <= N_);
                for (size_t n = 0; n < values.size(); n++) {
                    assert(values.data()[n].size() <= M_);
                    for (size_t m = 0; m < values.data()[n].size(); m++) {
                        data[n][m] = values.data()[n].data()[m];
                    }
                }
            }

            //Arithmetic
            //Add
            Matrix operator + (const Matrix& other) const {
                Matrix res;
                for (size_t n = 0; n < N_; n++) {
                    for (size_t m = 0; m < M_; m++) {
                        res[n][m] = data[n][m] + other.data[n][m];
                    }
                }
                return res;
            }

            //Sub
            Matrix operator - (const Matrix& other) const {
                Matrix res;
                for (size_t n = 0; n < N_; n++) {
                    for (size_t m = 0; m < M_; m++) {
                        res[n][m] = data[n][m] - other.data[n][m];
                    }
                }
                return res;
            }

            //Mul
            template<size_t K_>
            Matrix<T, N_, K_> operator * (const Matrix<T, M_, K_>& other) const {
                Matrix res;
                for (size_t n = 0; n < N_; n++) {
                    for (size_t k = 0; k < K_; k++) {
                        for (size_t m = 0; m < M_; m++) {
                            res[n][k] += data[n][m] * other.data[m][k];
                        }
                    }
                }
                return res;
            }

            //ScalarMul
            Matrix operator * (const T& scalar) const {
                Matrix res;
                for (size_t n = 0; n < N_; n++) {
                    for (size_t m = 0; m < M_; m++) {
                        res[n][m] = scalar * data[n][m];
                    }
                }
                return res;
            }

            //Det

            //Access
            T operator[](const size_t i, const size_t j) const {
                return data[i][j];
            }

            T& operator[](const size_t i, const size_t j) {
                return data[i][j];
            }
        };

        //Scalar multiplication
        template<typename T, size_t N_, size_t M_>
        static inline Matrix<T, N_, M_> operator * (const T& scalar, const Matrix<T, N_, M_>& mat) {
            return mat.operator*(scalar);
        }
    }

    template<typename T, size_t N_, size_t M_>
    using Matrix = detail::Matrix<T, N_, M_>;
}
