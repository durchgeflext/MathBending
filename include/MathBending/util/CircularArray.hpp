#pragma once
#include <cstddef>

template <typename T, size_t Cap>
struct CircularArray {
    private:
    T content[Cap];

    public:

    T *data() {
        return content;
    }

    T *data(const size_t idx) {
        return &content[idx % Cap];
    }

    constexpr T& operator[] (const size_t idx) {
        return content[idx % Cap];
    }

    constexpr const T& operator[](const size_t idx) const {
        return content[idx % Cap];
    }

    static constexpr size_t inc(const size_t idx, const size_t step) {
        return (idx + step) % Cap;
    }

    static constexpr size_t dec(const size_t idx, const size_t step) {
        return (idx + (Cap - step)) % Cap;
    }

    static constexpr size_t next(const size_t idx) {
        return inc(idx, 1);
    }

    static constexpr size_t prev(const size_t idx) {
        return dec(idx, 1);
    }
};
