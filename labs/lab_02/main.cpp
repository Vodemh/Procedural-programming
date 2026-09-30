#include <iostream>
#include <iomanip>
#include <cmath>

#include "exponential.h"

int main()
{
    double x;

    std::cout << "Enter x: ";
    std::cin >> x;

    double resultSeries = exponentialSeries(x);
    double resultImproved = exponentialImproved(x);

    std::cout << std::setprecision(15);

    std::cout << "Direct series:  "
              << resultSeries << '\n';

    std::cout << "Improved:       "
              << resultImproved << '\n';
    //для порівняння
    std::cout << "std::exp:       "
          << std::exp(x) << '\n';

    return 0;
}