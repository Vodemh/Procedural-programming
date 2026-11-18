#include "tasks.h"

#include <iostream>
#include <vector>

void task10c()
{
    std::vector<int> values{1, 2, 3, 4};
    const std::size_t original_size = values.size();
    for (std::size_t i = 0; i < original_size; ++i)
        if (values[i] % 2 == 0) values.push_back(values[i] * 10);
    for (int value : values) std::cout << value << ' ';
    std::cout << '\n';
}
