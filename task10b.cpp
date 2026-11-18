#include "tasks.h"

#include <cmath>
#include <iostream>

namespace
{
    double distance(double a, double b)
    {
        return std::abs(a - b);
    }
}

void task10b()
{
    std::cout << distance(0.25, 1.0) << '\n';
}
