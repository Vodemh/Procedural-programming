#ifndef SIMPSON_H
#define SIMPSON_H

#include <cstddef>
#include <functional>
#include <cmath>
#include <stdexcept>
#include <algorithm>


#ifndef NDEBUG
extern std::size_t functionCalls;
#endif


//метод Сімпсона на одному відрізку
double simpsonOnce(double a, double b, double fa, double fm, double fb);

//обчислення функції з підрахунком викликів
double evaluateFunction(const std::function<double(double)>& f, double x);

//рекурсивний адаптивний алгоритм Сімпсона
double adaptiveSimpson(
    const std::function<double(double)>& f,
    double a,
    double b,
    double fa,
    double fm,
    double fb,
    double whole,
    double eps,
    int depth
);

//основна шаблонна функція
template <typename F>
double Simpson(double a, double b, F f, double eps)
{
    if (eps <= 0 || !std::isfinite(eps)) {
        throw std::invalid_argument("Epsilon must be positive and finite");
    }

    if (!std::isfinite(a) || !std::isfinite(b)) {
        throw std::invalid_argument("Interval bounds must be finite");
    }

    if (a == b) {
        return 0.0;
    }

    // якщо межі задані у зворотному порядку
    double sign = 1.0;

    if (a > b) {
        std::swap(a, b);
        sign = -1.0;
    }


    std::function<double(double)> func = f;

    double mid = a + (b - a) / 2.0;

    double fa = evaluateFunction(func, a);
    double fm = evaluateFunction(func, mid);
    double fb = evaluateFunction(func, b);

    double whole = simpsonOnce(a, b, fa, fm, fb);

    return sign * adaptiveSimpson(
        func,
        a, b,
        fa, fm, fb,
        whole,
        eps,
        50
    );
}

#endif