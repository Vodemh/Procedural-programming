#include <cmath>

double chebyshev(double x, int n)
{
    if (n == 0)
        return 1.0;

    if (n == 1)
        return x;

    double u = 1.0; // T_0
    double v = x;   // T_1

    for (int k = 2; k <= n; k++)
    {
        double current = 2.0 * x * v - u;

        u = v;
        v = current;
    }

    return v;
};