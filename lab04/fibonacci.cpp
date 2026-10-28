#include "fibonacci.h"
#include <utility>


struct Matrix {
    ULL a, b, c, d;
};


// Множення двох матриць 2x2
static Matrix multiply(Matrix x, Matrix y) {
    return {
        x.a * y.a + x.b * y.c,
        x.a * y.b + x.b * y.d,
        x.c * y.a + x.d * y.c,
        x.c * y.b + x.d * y.d
    };
}


ULL fibonacciIterative(int n) {
    if (n <= 1) {
        return static_cast<ULL>(n);
    }

    ULL previous = 0;
    ULL current = 1;

    for (int i = 2; i <= n; ++i) {
        ULL next = previous + current;
        previous = current;
        current = next;
    }

    return current;
}


ULL fibonacciMatrix(int n) {
    Matrix result{1, 0, 0, 1};// одинична матриця 
    Matrix base{1, 1, 1, 0}; 
    // матричя основа, якщо піднести до степеня n,
    // то верхній правий елемент отриманої матриці буде n-те число Фібоначі

    while (n > 0) {
        if (n % 2 == 1) {
            result = multiply(result, base);
        }

        n /= 2;

        if (n > 0) {
            base = multiply(base, base);
        }
    }

    return result.b; //b - верхній правий елемент отриманої матриці
}



// Наївна рекурсія
ULL fibonacciRecursive(int n) {
    if (n <= 1) {
        return static_cast<ULL>(n);
    }

    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}



// Допоміжна функція швидкої рекурсії
static std::pair<ULL, ULL> fibonacciPair(int n) {
    if (n == 0) {
        return {0, 1};
    }

    auto [a, b] = fibonacciPair(n / 2);

    ULL c = a * (2 * b - a);
    ULL d = a * a + b * b;

    if (n % 2 == 0) {
        return {c, d};
    }

    return {d, c + d};
}

// Швидка рекурсія
ULL fibonacciFastRecursive(int n) {
    return fibonacciPair(n).first;
}