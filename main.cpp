// Підсумкова контрольна робота. Цей файл не змінюйте.
// Запуск:  KR            — усі задачі по черзі
//          KR 7          — задача 7
//          KR 10c 3      — програма (в) задачі 10 і задача 3
#include <iostream>
#include <string_view>
#include "tasks.h"

namespace
{
    struct Entry
    {
        std::string_view name;
        void (*run)();
    };

    constexpr Entry tasks[] = {
        {"1", task01}, {"2", task02}, {"3", task03}, {"4", task04}, {"5", task05},
        {"6", task06}, {"7", task07}, {"8", task08}, {"9", task09},
        {"10a", task10a}, {"10b", task10b}, {"10c", task10c}, {"10d", task10d}, {"10e", task10e},
    };

    void run(const Entry& t)
    {
        std::cout << "===== task " << t.name << " =====\n";
        t.run();
        std::cout << '\n';
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        for (const Entry& t : tasks) run(t);
        return 0;
    }
    for (int i = 1; i < argc; ++i)
    {
        const std::string_view wanted = argv[i];
        bool found = false;
        for (const Entry& t : tasks)
            if (t.name == wanted) { run(t); found = true; }
        if (!found)
        {
            std::cerr << "unknown task: " << wanted << '\n';
            return 1;
        }
    }
}
