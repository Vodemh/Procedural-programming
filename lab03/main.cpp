
#include "quick_sort.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

void testSort(std::vector<double> values) {
    const std::vector<double> original = values;

    quickSort(values);

    // Перевірка зростання елементів
    assert(std::is_sorted(values.begin(), values.end()));

    // Перевірка збереження всіх елементів
    std::vector<double> expected = original;
    std::sort(expected.begin(), expected.end());

    assert(values == expected);
}

int main() {
    testSort({});
    testSort({67.0});
    testSort({1.0, 2.0, 3.0, 4.0, 5.0});
    testSort({5.0, 4.0, 3.0, 2.0, 1.0});
    testSort({3.0, 1.0, 3.0, 2.0, 1.0});
    testSort({-2.5, 0.0, 7.23, -2.5, 1.67});

    std::cout << "All tests passed!\n";

    return 0;
}
