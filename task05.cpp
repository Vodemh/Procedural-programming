#include "tasks.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace
{
    struct Student
    {
        std::string name;
        int grade;
    };

    void print_students(const std::vector<Student>& students)
    {
        for (const Student& student : students)
            std::cout << student.name << ": " << student.grade << '\n';
    }

    bool same_order(const std::vector<Student>& a, const std::vector<Student>& b)
    {
        if (a.size() != b.size()) return false;
        for (std::size_t i = 0; i < a.size(); ++i)
            if (a[i].name != b[i].name || a[i].grade != b[i].grade) return false;
        return true;
    }
}

void task05()
{
    const std::vector<Student> students{
        {"Olena", 90}, {"Andrii", 85}, {"Maksym", 90},
        {"Iryna", 75}, {"Dmytro", 85}, {"Anna", 95}, {"Petro", 75}
    };
    const int threshold = 85;

    auto first = students;
    std::sort(first.begin(), first.end(), [](const Student& a, const Student& b)
    {
        if (a.grade != b.grade) return a.grade > b.grade;
        return a.name < b.name;
    });
    std::cout << "Sorted by grade and name:\n";
    print_students(first);

    const auto count = std::count_if(first.begin(), first.end(), [threshold](const Student& s)
    {
        return s.grade >= threshold;
    });
    std::cout << "At or above threshold: " << count << '\n';

    auto second = students;
    std::sort(second.begin(), second.end(), [](const Student& a, const Student& b)
    {
        return a.name < b.name;
    });
    std::stable_sort(second.begin(), second.end(), [](const Student& a, const Student& b)
    {
        return a.grade > b.grade;
    });
    std::cout << "Two-pass sorting matches: " << std::boolalpha << same_order(first, second) << '\n';
}
