#include "quick_sort.h"

#include <algorithm>
#include <cstddef>

namespace{
    void quickSortRange( std::vector<double>& values, std::size_t left, std::size_t right){
        if(left >= right){
            return;
        }
        const double pivot = values[left + (right - left) / 2];

        std::size_t i = left;
        std::size_t j = right;

        while (i <= j){
            while (values[i] < pivot){
                ++i;
            }

            while (values[j] > pivot){
                if (j == 0){
                    break;
                }
                --j;
            }

            if (i <= j){
                std::swap(values[i], values[j]);
                ++i;

                if (j ==0) {
                    break;
                }
                --j;
            }
            
        }

        if (left < j){
            quickSortRange(values, left, j);
        }

        if (i < right){
            quickSortRange(values, i, right);
        }
    }


} //namespace

// функція обгортка
void quickSort(std::vector<double>& values){
    if (values.size() < 2){
        return;
    }

    quickSortRange(values, 0, values.size() - 1);
}