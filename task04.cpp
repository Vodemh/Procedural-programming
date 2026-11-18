#include "tasks.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numbers>

namespace
{
    struct SinResult
    {
        double value;
        std::size_t terms;
        double max_term;
    };

    SinResult taylor_sin(double x, double eps = 1e-15)
    {
        if (x == 0.0) return {0.0, 1, 0.0};

        double term = x;
        double sum = x;
        double max_term = std::abs(term);
        std::size_t terms = 1;

        for (std::size_t n = 1; n < 10000; ++n)
        {
            const double dn = static_cast<double>(n);
            term *= -(x * x) / (2.0 * dn * (2.0 * dn + 1.0));
            if (!std::isfinite(term))
                return {std::numeric_limits<double>::quiet_NaN(), terms, std::numeric_limits<double>::infinity()};

            sum += term;
            ++terms;
            if (!std::isfinite(sum))
                return {sum, terms, std::max(max_term, std::abs(term))};
            max_term = std::max(max_term, std::abs(term));
            if (std::abs(term) <= eps * std::abs(sum)) break;
        }
        return {sum, terms, max_term};
    }

    double reduced_sin(double x)
    {
        const double pi = std::numbers::pi;
        double r = std::remainder(x, 2.0 * pi);
        if (r > pi / 2.0) r = pi - r;
        else if (r < -pi / 2.0) r = -pi - r;
        return taylor_sin(r).value;
    }

    double relative_error(double calculated, double reference)
    {
        if (!std::isfinite(calculated)) return std::numeric_limits<double>::infinity();
        if (reference == 0.0) return std::abs(calculated - reference);
        return std::abs(calculated - reference) / std::abs(reference);
    }
}

void task04()
{
    const double xs[]{0.5, 1, 3, 10, 20, 30, 40, 100, 1000};
    std::cout << std::scientific << std::setprecision(6);
    std::cout << "x\tstd::sin(x)\tdirect_error\tterms\tmax_term\treduced_error\n";
    for (double x : xs)
    {
        const SinResult direct = taylor_sin(x);
        const double reference = std::sin(x);
        const double reduced = reduced_sin(x);
        std::cout << x << '\t' << reference << '\t'
                  << relative_error(direct.value, reference) << '\t'
                  << direct.terms << '\t' << direct.max_term << '\t'
                  << relative_error(reduced, reference) << '\n';
    }
}
