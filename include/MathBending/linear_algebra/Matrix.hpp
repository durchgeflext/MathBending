#pragma once

#include <array>
#include <cstdarg>
#include <cstddef>

namespace MathBending {
    namespace detail {
        template<typename T, size_t N_, size_t M_>
        struct Matrix {
            std::array<std::array<T, M_>, N_> data;

            explicit Matrix() = default;
            explicit Matrix(Matrix& mat) = default;
            explicit Matrix(Matrix&& mat) = default;
            ~Matrix() = default;

            explicit Matrix(T value) {
                for (size_t i = 0; i < N_; i++) {
                    for (size_t j = 0; j < M_; j++) {
                        data[i][j] = value;
                    }
                }
            }

            explicit Matrix(T values...) {
                static_assert(values <= N_ * M_);
                std::va_list vals;
                va_start(vals, values);
                for (size_t i = 0; i < values; i++) {
                    data[i / N_][i % N_] = va_arg(vals, T);
                }
                va_end(vals);
            }
        };
    }

    template<typename T, size_t N_, size_t M_>
    using Matrix = detail::Matrix<T, N_, M_>;
}
