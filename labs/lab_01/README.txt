компіляція:
g++ -std=c++17 -O2 -Wall -Wextra main.cpp power.cpp -o power



Correctness test passed!
x = 2.000000, n = 10
Result = 1024.000000

power:           10 multiplications
quickPower:      6 multiplications
power_rec:       11 calls
quickPower_rec:  5 calls

n = 0 test passed!


Step comparison:
n = 1000000
power steps = 1000000
quickPower steps = 27


Time comparison (100 repetitions):
power:          3143 us
quickPower:     3 us
power_rec:      5942 us
quickPower_rec: 7 us

Швидкий спосіб значно зменшує кількість операцій через логарифмічну залежність.
power - O(n)
quickPower - O(log n)
Тому час виконання на прикладі 3 мікросекунди замість 3143.
Видно що час виконання рекурсії трохи більший через затрати на виклики функції та доступу до стеку.