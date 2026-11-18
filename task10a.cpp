#include "tasks.h"

#include <iostream>
#include <string>
#include <string_view>

namespace
{
    std::string greeting(std::string_view name)
    {
        return "Hello, " + std::string(name) + "! Nice to see you.";
    }
}

void task10a()
{
    std::cout << greeting("Olena") << '\n';
}
