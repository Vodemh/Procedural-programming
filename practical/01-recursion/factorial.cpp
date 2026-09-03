#include <cmath>

long long factorial(int n)
{
    long long x = 1;

    for (int k = 1; k <= n; k++)
    {
        x = x * k;
    }

    return x;
};