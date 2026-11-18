#include "tasks.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

namespace
{
    using Matrix = std::array<std::array<std::int64_t, 4>, 4>;

    Matrix operator*(const Matrix& a, const Matrix& b)
    {
        Matrix result{};
        constexpr std::int64_t limit = std::numeric_limits<std::int64_t>::max();
        for (std::size_t i = 0; i < 4; ++i)
            for (std::size_t j = 0; j < 4; ++j)
                for (std::size_t k = 0; k < 4; ++k)
                {
                    if (a[i][k] != 0 && b[k][j] > limit / a[i][k])
                        throw std::overflow_error("Tetranacci matrix multiplication overflow");
                    const std::int64_t product = a[i][k] * b[k][j];
                    if (result[i][j] > limit - product)
                        throw std::overflow_error("Tetranacci matrix sum overflow");
                    result[i][j] += product;
                }
        return result;
    }

    Matrix matrix_power(Matrix base, std::size_t exponent)
    {
        Matrix result{};
        for (std::size_t i = 0; i < 4; ++i) result[i][i] = 1;
        while (exponent > 0)
        {
            if (exponent % 2 == 1) result = result * base;
            exponent /= 2;
            if (exponent > 0) base = base * base;
        }
        return result;
    }

    Matrix transition_matrix()
    {
        return Matrix{{{{1, 1, 1, 1}}, {{1, 0, 0, 0}}, {{0, 1, 0, 0}}, {{0, 0, 1, 0}}}};
    }

    std::int64_t tetranacci(std::size_t n)
    {
        if (n < 3) return 0;
        if (n == 3) return 1;
        return matrix_power(transition_matrix(), n - 3)[0][0];
    }

    bool can_add_four(std::int64_t a, std::int64_t b, std::int64_t c, std::int64_t d)
    {
        const auto limit = std::numeric_limits<std::int64_t>::max();
        if (a > limit - b) return false;
        const auto ab = a + b;
        if (ab > limit - c) return false;
        const auto abc = ab + c;
        return abc <= limit - d;
    }
}

void task07()
{
    std::cout << "Tetranacci T0..T12: ";
    for (std::size_t n = 0; n <= 12; ++n) std::cout << tetranacci(n) << ' ';
    std::cout << '\n';

    std::vector<std::int64_t> simple{0, 0, 0, 1};
    std::size_t max_n = 3;
    while (can_add_four(simple[max_n], simple[max_n - 1], simple[max_n - 2], simple[max_n - 3]))
    {
        const std::int64_t next = simple[max_n] + simple[max_n - 1] + simple[max_n - 2] + simple[max_n - 3];
        simple.push_back(next);
        ++max_n;
    }

    bool matches = true;
    for (std::size_t n = 0; n <= max_n; ++n)
        if (tetranacci(n) != simple[n]) { matches = false; break; }

    std::cout << "Matrix matches simple algorithm: " << std::boolalpha << matches << '\n';
    std::cout << "Maximum n for int64_t: " << max_n << '\n';
    std::cout << "T(" << max_n << ") = " << simple[max_n] << '\n';
}
