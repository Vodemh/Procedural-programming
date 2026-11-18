#include "tasks.h"

#include <array>
#include <cstddef>
#include <iostream>
#include <span>
#include <vector>

namespace
{
    template <class T>
    void reverse_range(std::span<T> s, std::size_t first, std::size_t last)
    {
        while (first < last)
        {
            --last;
            if (first >= last) break;
            T temp = s[first];
            s[first] = s[last];
            s[last] = temp;
            ++first;
        }
    }

    template <class T>
    void rotate_right(std::span<T> s, std::size_t k)
    {
        if (s.empty()) return;
        k %= s.size();
        if (k == 0) return;
        reverse_range(s, 0, s.size());
        reverse_range(s, 0, k);
        reverse_range(s, k, s.size());
    }

    template <class T>
    void print_range(std::span<const T> s)
    {
        for (const T& value : s) std::cout << value << ' ';
        std::cout << '\n';
    }
}

void task01()
{
    std::vector<int> values{1, 2, 3, 4, 5, 6, 7};
    rotate_right(std::span<int>(values), 3);
    std::cout << "Vector, k=3: ";
    print_range(std::span<const int>(values));

    std::array<double, 5> decimals{1.1, 2.2, 3.3, 4.4, 5.5};
    rotate_right(std::span<double>(decimals), 12);
    std::cout << "Array, k=12: ";
    print_range(std::span<const double>(decimals));

    char letters[4]{'a', 'b', 'c', 'd'};
    rotate_right(std::span<char>(letters), 4);
    std::cout << "C array, k=4: ";
    print_range(std::span<const char>(letters));

    std::vector<int> empty;
    rotate_right(std::span<int>(empty), 5);
    std::cout << "Empty vector size: " << empty.size() << '\n';
}
