#include "tasks.h"

#include <iostream>
#include <span>
#include <stdexcept>

namespace
{
    double average(std::span<const double> values)
    {
        if (values.empty()) throw std::invalid_argument("Cannot average an empty range");
        double sum = 0.0;
        for (double value : values) sum += value;
        return sum / static_cast<double>(values.size());
    }
}

void task10e()
{
    const double marks[]{90, 80, 70, 60, 50};
    std::cout << average(std::span<const double>(marks)) << '\n';
}
