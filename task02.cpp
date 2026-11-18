#include "tasks.h"

#include <iostream>
#include <string>
#include <string_view>
#include <vector>

namespace
{
    std::vector<std::string_view> split(std::string_view text, char sep)
    {
        std::vector<std::string_view> parts;
        std::size_t start = 0;

        for (std::size_t i = 0; i < text.size(); ++i)
        {
            if (text[i] == sep)
            {
                parts.push_back(text.substr(start, i - start));
                start = i + 1;
            }
        }
        parts.push_back(text.substr(start));
        return parts;
    }

    void print_parts(const std::vector<std::string_view>& parts)
    {
        std::cout << '[';
        for (std::size_t i = 0; i < parts.size(); ++i)
        {
            if (i != 0) std::cout << "] [";
            std::cout << parts[i];
        }
        std::cout << "]\n";
    }
}

void task02()
{
    std::cout << "a,,b: ";
    print_parts(split("a,,b", ','));
    std::cout << ",a,: ";
    print_parts(split(",a,", ','));
    std::cout << "Empty string: ";
    print_parts(split("", ','));
    std::cout << "No separator: ";
    print_parts(split("hello", ','));

    const std::string date = "2026-10-17";
    const auto date_parts = split(date, '-');
    std::cout << "Date: ";
    print_parts(date_parts);

    const std::string source = "a,b,c";
    const auto safe_parts = split(source, ',');
    std::cout << "Safe source: ";
    print_parts(safe_parts);
}
