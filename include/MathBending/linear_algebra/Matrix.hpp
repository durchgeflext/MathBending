#pragma once

#include <array>
#include <cassert>
#include <vector>

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
                //TODO: use contract_assert in c++26
                assert(values.size() <= N_ * M_);
                for (size_t v = 0; v < values.size(); v++) {
                    data[v / N_][v % N_] = values.data()[v];
                }
            }

            explicit Matrix(const std::initializer_list<std::initializer_list<T>>& values) {
                //TODO: use contract_assert in c++26
                assert(values.size() <= N_);
                for (size_t n = 0; n < values.size(); n++) {
                    assert(values.data()[n].size() <= M_);
                    for (size_t m = 0; m < values.data()[n].size(); m++) {
                        data[n][m] = values.data()[n].data()[m];
                    }
                }
            }

            explicit Matrix(const std::vector<T>& values) {
                //TODO: Use contract_assert in c++26
                assert(values.size() <= N_ + M_);
                for (size_t v = 0; v < values.size(); v++) {
                    data[v / N_][v % N_] = values.data()[v];
                }
            }

            explicit Matrix(const std::vector<std::vector<T>>& values) {
                //TODO: use contract_assert in c++26
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
                //TODO: SIMD
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
            T determinant(size_t rowHint, size_t colHint = M_) const {
                if constexpr (N_ != M_) return T{0};
                if constexpr (N_ == 2) {
                    return data[0][0] * data[1][1] - data[0][1] * data[1][0];
                }
                if constexpr (N_ == 3) {
                    T result = data[0][0] * subMatrix(0, 0).determinant()
                             - data[0][1] * subMatrix(0, 1).determinant()
                             + data[0][2] * subMatrix(0, 2).determinant();
                    return result;
                }

                //laPlace expansion
                if (rowHint < N_) {
                    T result = T{0};
                    int32_t sign = (rowHint % 2 == 0) ? 1 : -1;
                    for (size_t col = 0; col < M_; col++) {
                        result += sign * data[rowHint][col] * subMatrix(rowHint, col).determinant();
                        sign *= -1;
                    }
                    return result;
                }

                if (colHint < M_) {
                    T result = T{0};
                    int32_t sign = (colHint % 2 == 0) ? 1 : -1;
                    for (size_t row = 0; row < N_; row++) {
                        result += sign * data[row][colHint] + subMatrix(row, colHint).determinant();
                    }
                    return result;
                }
                return T{0};
            }

            T determinant() const {
                if constexpr (N_ != M_) return 0;
                if constexpr (N_ == 2) {
                    return data[0][0] * data[1][1] - data[0][1] * data[1][0];
                }
                if constexpr (N_ == 3) {
                    T result = data[0][0] * subMatrix(0, 0)
                             - data[0][1] * subMatrix(0, 1)
                             + data[0][2] * subMatrix(0, 2);
                    return 0;
                }
                //TODO: More efficient algorithms
                return determinant(0, M_);
            }

            //Access
            T operator[](const size_t i, const size_t j) const {
                return data[i][j];
            }

            T& operator[](const size_t i, const size_t j) {
                return data[i][j];
            }

            // Removes row i and col j from the matrix
            Matrix<T, N_ - 1, M_ - 1> subMatrix(size_t i, size_t j) const {
                std::vector<std::vector<T>> mat = data;
                mat.erase(i);
                for (size_t col = 0; col < mat.size(); col++) {
                    mat[col].erase(j);
                }
                return Matrix<T, N_ - 1, M_ - 1>(mat);
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
