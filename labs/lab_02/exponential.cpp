#include "exponential.h"

#include <cmath>

double exponentialSeries(double x){

    const double precision = 1e-12;

    double sum = 1.0;
    double term = 1.0;

    for (int n = 1; ; n++)
    {
        term *= x / n;
        sum += term;

        if (std::abs(term) < precision)
        {
            break;
        }
    }

    return sum;
}

double exponentialImproved(double x)
{
    if (x < 0)//перевірка від'ємного значення, щоб рахувати додатнє число
    {
        return 1.0 / exponentialImproved(-x);
    }

    int integerPart = static_cast<int>(std::floor(x));//виділяємо цілу частину
    double fractionalPart = x - integerPart;//дробова частина

    double e = exponentialSeries(1.0);

    double integerPartResult = 1.0;

    for (int i = 0; i < integerPart; i++)
    {
        integerPartResult *= e;
    }

    double fractionalPartResult = exponentialSeries(fractionalPart);

    return integerPartResult * fractionalPartResult;//x^n, n=6.7 наприклад то x^n=(x^6)*(x^0.7);
}
