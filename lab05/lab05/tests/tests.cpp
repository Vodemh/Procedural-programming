#include "simpson.h"

#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>


double square(double x) {
    return x * x;
}


void runTest(
    const std::string& name,
    double a,
    double b,
    auto f,
    double exact,
    double eps
) {
#ifndef NDEBUG
    functionCalls = 0;
#endif

    try {
        double result = Simpson(a, b, f, eps);
        double error = std::abs(result - exact);

        std::cout << name << '\n';
        std::cout << "Result: " << result << '\n';
        std::cout << "Exact:  " << exact << '\n';
        std::cout << "Error:  " << error << '\n';

#ifndef NDEBUG
        std::cout << "Function calls: " << functionCalls << '\n';
#endif

        if (error <= eps) {
            std::cout << "Test PASSED\n\n";
        } else {
            std::cout << "Test FAILED\n\n";
        }
    }
    catch (const std::exception& e) {
        std::cout << name << '\n';
        std::cout << "Error: " << e.what() << "\n\n";
    }
}

int main() {
    const double eps = 1e-8;

    std::cout << std::fixed << std::setprecision(12);

    //звичайна функція: f(x) = x^2
    //інтеграл від -2 до 3 = 35/3
    runTest(
        "Test 1: x^2",
        -2.0, 3.0,
        square,
        35.0 / 3.0,
        eps
    );

    //лямбда: f(x) = x^4
    //інтеграл від -1 до 2 = 33/5
    runTest(
        "Test 2: x^4 (lambda)",
        -1.0, 2.0,
        [](double x) {
            return x * x * x * x;
        },
        33.0 / 5.0,
        eps
    );

    //лямбда: f(x) = sin(x)
    //інтеграл від 0 до pi = 2
    runTest(
        "Test 3: sin(x)",
        0.0, M_PI,
        [](double x) {
            return std::sin(x);
        },
        2.0,
        eps
    );

    //лямбда: f(x) = exp(x)
    //інтеграл від 0 до 1 дорівнює e - 1
    runTest(
        "Test 4: exp(x)",
        0.0, 1.0,
        [](double x) {
            return std::exp(x);
        },
        std::exp(1.0) - 1.0,
        eps
    );

   
    runTest(
        "Test 5: reversed interval",
        3.0, -2.0,
        square,
        -35.0 / 3.0,
        eps
    );

  
    runTest(
        "Test 6: zero interval",
        2.0, 2.0,
        square,
        0.0,
        eps
    );

    return 0;
}