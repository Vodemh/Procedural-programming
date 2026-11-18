#include "tasks.h"

#include <iostream>
#include <span>
#include <vector>

namespace
{
    std::vector<int> squares(int n)
    {
        std::vector<int> values;
        for (int i = 1; i <= n; ++i) values.push_back(i * i);
        return values;
    }
}

void task10d()
{
    const std::vector<int> values = squares(5);
    const std::span<const int> view(values);
    for (int value : view) std::cout << value << ' ';
    std::cout << '\n';
}
