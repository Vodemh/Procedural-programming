компіляція g++ -std=c++20 -Wall -Wextra -Wpedantic -g -Iinclude src/simpson.cpp tests/tests.cpp -o tests_debug

Test 1: x^2
Result: 11.666666666667
Exact:  11.666666666667
Error:  0.000000000000
Function calls: 5
Test PASSED

Test 2: x^4 (lambda)
Result: 6.600000000000
Exact:  6.600000000000
Error:  0.000000000000
Function calls: 257
Test PASSED

Test 3: sin(x)
Result: 1.999999999998
Exact:  2.000000000000
Error:  0.000000000002
Function calls: 121
Test PASSED

Test 4: exp(x)
Result: 1.718281828461
Exact:  1.718281828459
Error:  0.000000000002
Function calls: 45
Test PASSED

Test 5: reversed interval
Result: -11.666666666667
Exact:  -11.666666666667
Error:  0.000000000000
Function calls: 5
Test PASSED

Test 6: zero interval
Result: 0.000000000000
Exact:  0.000000000000
Error:  0.000000000000
Function calls: 0
Test PASSED

Точність досягається через рекурсивне ділення нашого проміжку та перевірку точності. Спочатку рахуємо 1 раз методом Сімпсона інтеграл за 3 точками a-старт, b-кінець, m-середина, потім рахуємо так само але розділивши відрізок навпіл, тепер рахуємо різницю між сумою площь 2 половин та попереднього порахованого відрізка удвічі більшого, якщо різниця менша за 15*точність
Таким чином, задана точність досягається шляхом послідовного поділу відрізка та контролю оцінки похибки на кожному кроці