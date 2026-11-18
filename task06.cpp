#include "tasks.h"

#include <cstddef>
#include <iostream>
#include <vector>

namespace
{
    struct IntArray
    {
        int* data = nullptr;
        std::size_t size = 0;
        std::size_t capacity = 0;
    };

    void push_back(IntArray& a, int value)
    {
        if (a.size == a.capacity)
        {
            const std::size_t new_capacity = (a.capacity == 0) ? 1 : a.capacity * 2;
            int* new_data = new int[new_capacity];
            for (std::size_t i = 0; i < a.size; ++i) new_data[i] = a.data[i];
            delete[] a.data;
            a.data = new_data;
            a.capacity = new_capacity;
        }
        a.data[a.size] = value;
        ++a.size;
    }

    void destroy(IntArray& a)
    {
        delete[] a.data;
        a.data = nullptr;
        a.size = 0;
        a.capacity = 0;
    }
}

void task06()
{
    IntArray own;
    std::vector<int> standard;
    std::size_t own_reallocations = 0;
    std::size_t vector_reallocations = 0;
    std::size_t old_own_capacity = own.capacity;
    std::size_t old_vector_capacity = standard.capacity();

    for (int n = 1; n <= 40; ++n)
    {
        push_back(own, n);
        standard.push_back(n);
        const bool own_changed = own.capacity != old_own_capacity;
        const bool vector_changed = standard.capacity() != old_vector_capacity;
        if (own_changed || vector_changed)
        {
            std::cout << "n=" << n << ", own capacity=" << own.capacity
                      << ", vector capacity=" << standard.capacity() << '\n';
        }
        if (own_changed) ++own_reallocations;
        if (vector_changed) ++vector_reallocations;
        old_own_capacity = own.capacity;
        old_vector_capacity = standard.capacity();
    }
    std::cout << "Own reallocations: " << own_reallocations << '\n';
    std::cout << "Vector reallocations: " << vector_reallocations << '\n';
    destroy(own);
}
