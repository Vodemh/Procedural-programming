#include "tasks.h"

#include <algorithm>
#include <compare>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <vector>

namespace
{
    struct Rational
    {
        long long num;
        long long den;
    };

    Rational create(long long num, long long den = 1)
    {
        if (den == 0) throw std::invalid_argument("Denominator cannot be zero");
        if (den < 0) { num = -num; den = -den; }
        const long long divisor = std::gcd(num, den);
        return {num / divisor, den / divisor};
    }

    Rational operator+(Rational a, Rational b)
    { return create(a.num * b.den + b.num * a.den, a.den * b.den); }
    Rational operator-(Rational a, Rational b)
    { return create(a.num * b.den - b.num * a.den, a.den * b.den); }
    Rational operator*(Rational a, Rational b)
    { return create(a.num * b.num, a.den * b.den); }

    Rational operator+(Rational a, int b) { return a + create(b); }
    Rational operator+(int a, Rational b) { return create(a) + b; }
    Rational operator-(Rational a, int b) { return a - create(b); }
    Rational operator-(int a, Rational b) { return create(a) - b; }
    Rational operator*(Rational a, int b) { return a * create(b); }
    Rational operator*(int a, Rational b) { return create(a) * b; }

    bool operator==(Rational a, Rational b)
    { return a.num == b.num && a.den == b.den; }

    std::strong_ordering operator<=>(Rational a, Rational b)
    { return (a.num * b.den) <=> (b.num * a.den); }

    std::ostream& operator<<(std::ostream& out, Rational value)
    { return out << value.num << '/' << value.den; }
}

void task08()
{
    const Rational a = create(2, 4);
    const Rational b = create(3, -6);
    std::cout << "a=" << a << ", b=" << b << '\n';
    std::cout << "a+b=" << a + b << ", a-b=" << a - b << ", a*b=" << a * b << '\n';
    std::cout << "a+2=" << a + 2 << ", 2+a=" << 2 + a << '\n';
    std::cout << "a-2=" << a - 2 << ", 2-a=" << 2 - a << '\n';
    std::cout << "a*3=" << a * 3 << ", 3*a=" << 3 * a << '\n';
    std::cout << std::boolalpha
              << "== " << (a == b) << ", != " << (a != b)
              << ", < " << (a < b) << ", > " << (a > b)
              << ", <= " << (a <= b) << ", >= " << (a >= b) << '\n';

    std::vector<Rational> values{create(3, 4), create(1, 2), create(2, 3), create(-1, 4)};
    std::sort(values.begin(), values.end());
    std::cout << "Sorted: ";
    for (Rational value : values) std::cout << value << ' ';
    std::cout << '\n';

    try { static_cast<void>(create(1, 0)); }
    catch (const std::invalid_argument& error) { std::cout << "Exception: " << error.what() << '\n'; }
}
