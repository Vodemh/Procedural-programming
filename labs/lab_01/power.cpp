#include "power.h"

double power(double x, unsigned int n, unsigned long long& steps)

{
    double result = 1.0;

    steps = 0;
    for (unsigned int i = 0; i < n; ++i)
    {
        result *= x;
        ++steps;
    }

    return result;
    
}

double quickPower(double x, unsigned int n, unsigned long long& steps)
{
    double result = 1.0;
    steps = 0;

    while(n > 0)
    {
        if (n % 2 == 1)
        {
            result *= x;
            ++steps;
        }

        x *= x;
        ++steps;

        n /= 2;
    }

    return result;
}

//recursion

double power_rec(double x, unsigned int n, unsigned long long& calls) 
{ 
    ++calls; 

    if (n == 0) 
    { 
        return 1.0; 
    } 

    return x * power_rec(x, n - 1, calls); 
}


double quickPower_rec(double x, unsigned int n, unsigned long long& calls) 
{ 
    ++calls; 

    if (n == 0) 
    { 
        return 1.0; 
    } 

    double half = quickPower_rec(x, n / 2, calls);

    if (n % 2 == 0)
    {
        return half * half;
    }

    return x * half * half; 
}