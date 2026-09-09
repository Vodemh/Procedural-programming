#include <cmath>

double exponentialSeries(double x, int n)
{
    double a = 1.0;  // a_0
    double S = 1.0;  // S_0

    for (int k = 1; k <= n; k++)
    {
        a = a * x / k;
        S = S + a;
    }

    return S;
};