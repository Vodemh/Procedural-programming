#include "tasks.h"

#include <chrono>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <span>
#include <stdexcept>
#include <vector>

namespace
{
    struct Triplet { std::size_t row, col; double value; };
    struct SparseMatrix { std::size_t rows, cols; std::vector<Triplet> items; };
    struct DenseMatrix { std::size_t rows, cols; std::vector<double> data; };

    DenseMatrix toDense(const SparseMatrix& matrix)
    {
        DenseMatrix result{matrix.rows, matrix.cols, std::vector<double>(matrix.rows * matrix.cols, 0.0)};
        for (const Triplet& item : matrix.items)
        {
            if (item.row >= matrix.rows || item.col >= matrix.cols)
                throw std::out_of_range("Sparse matrix coordinate out of range");
            result.data[item.row * matrix.cols + item.col] = item.value;
        }
        return result;
    }

    std::vector<double> operator*(const SparseMatrix& matrix, std::span<const double> vector)
    {
        if (matrix.cols != vector.size()) throw std::invalid_argument("Dimension mismatch");
        std::vector<double> result(matrix.rows, 0.0);
        for (const Triplet& item : matrix.items)
        {
            if (item.row >= matrix.rows || item.col >= matrix.cols)
                throw std::out_of_range("Sparse matrix coordinate out of range");
            result[item.row] += item.value * vector[item.col];
        }
        return result;
    }

    std::vector<double> operator*(const DenseMatrix& matrix, std::span<const double> vector)
    {
        if (matrix.cols != vector.size()) throw std::invalid_argument("Dimension mismatch");
        if (matrix.data.size() != matrix.rows * matrix.cols)
            throw std::invalid_argument("Invalid dense matrix storage");
        std::vector<double> result(matrix.rows, 0.0);
        for (std::size_t row = 0; row < matrix.rows; ++row)
            for (std::size_t col = 0; col < matrix.cols; ++col)
                result[row] += matrix.data[row * matrix.cols + col] * vector[col];
        return result;
    }

    SparseMatrix make_tridiagonal(std::size_t n)
    {
        SparseMatrix matrix{n, n, {}};
        matrix.items.reserve(n == 0 ? 0 : 3 * n - 2);
        for (std::size_t i = 0; i < n; ++i)
        {
            matrix.items.push_back({i, i, 2.0});
            if (i > 0) matrix.items.push_back({i, i - 1, -1.0});
            if (i + 1 < n) matrix.items.push_back({i, i + 1, -1.0});
        }
        return matrix;
    }

    bool equal_results(const std::vector<double>& a, const std::vector<double>& b)
    {
        if (a.size() != b.size()) return false;
        for (std::size_t i = 0; i < a.size(); ++i)
            if (std::abs(a[i] - b[i]) > 1e-12) return false;
        return true;
    }
}

void task09()
{
    const SparseMatrix small = make_tridiagonal(5);
    const double input[]{1, 2, 3, 4, 5};
    const auto small_result = small * std::span<const double>(input);
    std::cout << "5x5 result: ";
    for (double value : small_result) std::cout << value << ' ';
    std::cout << '\n';

    constexpr std::size_t n = 1000;
    const SparseMatrix sparse = make_tridiagonal(n);
    const DenseMatrix dense = toDense(sparse);
    std::vector<double> vector(n);
    for (std::size_t i = 0; i < n; ++i) vector[i] = std::sin(0.01 * static_cast<double>(i));

    const auto sparse_start = std::chrono::steady_clock::now();
    const auto sparse_result = sparse * std::span<const double>(vector);
    const auto sparse_end = std::chrono::steady_clock::now();
    const auto dense_start = std::chrono::steady_clock::now();
    const auto dense_result = dense * std::span<const double>(vector);
    const auto dense_end = std::chrono::steady_clock::now();

    const double sparse_ms = std::chrono::duration<double, std::milli>(sparse_end - sparse_start).count();
    const double dense_ms = std::chrono::duration<double, std::milli>(dense_end - dense_start).count();
    std::cout << "Results match: " << std::boolalpha << equal_results(sparse_result, dense_result) << '\n';
    std::cout << "Sparse multiplication: " << sparse_ms << " ms\n";
    std::cout << "Dense multiplication: " << dense_ms << " ms\n";
    std::cout << "Sparse storage: " << sparse.items.capacity() * sizeof(Triplet) << " bytes\n";
    std::cout << "Dense storage: " << dense.data.capacity() * sizeof(double) << " bytes\n";
}
