#include "simpson.h"

#include <cmath>
#include <stdexcept>
#include <algorithm>

#ifndef NDEBUG
std::size_t functionCalls = 0;
#endif

//обчислення функції з підрахунком викликів
double evaluateFunction(const std::function<double(double)>& f, double x) {
    #ifndef NDEBUG
        ++functionCalls;
    #endif

    return f(x);
}


double simpsonOnce(double a, double b, double fa, double fm, double fb) {
    return (b - a) / 6.0 * (fa + 4.0 * fm + fb);// формула Сімпсона
}



// рекурсивний адаптивний алгоритм Сімпсона
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
) {
    double mid = a + (b - a) / 2.0;

    double leftMid = a + (mid - a) / 2.0;
    double rightMid = mid + (b - mid) / 2.0;

    if (leftMid == a || rightMid == b) {
        return whole;
    }


    double flm = evaluateFunction(f, leftMid);
    double frm = evaluateFunction(f, rightMid);


    double left = simpsonOnce(a, mid, fa, flm, fm);
    double right = simpsonOnce(mid, b, fm, frm, fb);

    //різниця між двома наближеннями - по факту наша точність
    double delta = left + right - whole;


    if (std::abs(delta) <= 15.0 * eps) {//15 - коефіцієнт згладження
        return left + right + delta / 15.0;
    }

  
    if (depth <= 0) {
        throw std::runtime_error("Maximum recursion depth reached");
    }


    return adaptiveSimpson(f, a, mid, fa, flm, fm, left, eps / 2.0, depth - 1) +
    adaptiveSimpson(f, mid, b, fm, frm, fb, right, eps / 2.0, depth - 1);
}