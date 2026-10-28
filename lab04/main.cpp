#include "fibonacci.h"

#include <chrono>
#include <iostream>

using Clock = std::chrono::steady_clock;

template <typename Function>
long long measureTime(Function function, int n) {
    auto start = Clock::now();

    volatile ULL result = function(n);
    (void)result;

    auto finish = Clock::now();

    return std::chrono::duration_cast<
        std::chrono::nanoseconds
    >(finish - start).count();
}

int main() {
    int n;

    std::cout << "Enter n (0..91): ";

    if (!(std::cin >> n) || n < 0 || n > 91) {
        std::cerr << "Enter a value from 0 to 91\n";
        return 1;
    }

    ULL iterative = fibonacciIterative(n);
    ULL matrix = fibonacciMatrix(n);
    ULL recursive = fibonacciRecursive(n);
    ULL fastRecursive = fibonacciFastRecursive(n);

    std::cout << "\nF(" << n << "):\n";
    std::cout << "Iterative:       " << iterative << '\n';
    std::cout << "Matrix:          " << matrix << '\n';
    std::cout << "Naive recursive: " << recursive << '\n';
    std::cout << "Fast recursive:  " << fastRecursive << '\n';

    if (iterative != matrix ||
        iterative != recursive ||
        iterative != fastRecursive) {
        std::cerr << "ERROR: results do not match!\n";
        return 1;
    }

    std::cout << "\nExecution time (nanoseconds):\n";
    std::cout << "Iterative:       "
              << measureTime(fibonacciIterative, n) << '\n';
    std::cout << "Matrix:          "
              << measureTime(fibonacciMatrix, n) << '\n';
    std::cout << "Naive recursive: "
              << measureTime(fibonacciRecursive, n) << '\n';
    std::cout << "Fast recursive:  "
              << measureTime(fibonacciFastRecursive, n) << '\n';

    return 0;
}