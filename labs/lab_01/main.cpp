#include <cassert>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>

#include "power.h"

using namespace std;


// Checking all four funcions
void testCorrectness()
{
    double x = 2.0;
    unsigned int n = 10;

    unsigned long long powerSteps = 0;
    unsigned long long quickSteps = 0;
    unsigned long long powerCalls = 0;
    unsigned long long quickCalls = 0;

    double expected = power(x, n, powerSteps);

    double quickResult = quickPower(x, n, quickSteps);
    double recursiveResult = power_rec(x, n, powerCalls);
    double quickRecursiveResult = quickPower_rec(x, n, quickCalls);

    assert(fabs(expected - quickResult) < 1e-9);
    assert(fabs(expected - recursiveResult) < 1e-9);
    assert(fabs(expected - quickRecursiveResult) < 1e-9);

    cout << "Correctness test passed!" << endl;

    cout << fixed << setprecision(6);

    cout << "x = " << x << ", n = " << n << endl;
    cout << "Result = " << expected << endl;

    cout << endl;

    cout << "power:           " << powerSteps << " multiplications" << endl;
    cout << "quickPower:      " << quickSteps << " multiplications" << endl;
    cout << "power_rec:       " << powerCalls << " calls" << endl;
    cout << "quickPower_rec:  " << quickCalls << " calls" << endl;
}


// checking n = 0
void testZeroPower()
{
    unsigned long long steps = 0;
    unsigned long long calls = 0;

    assert(power(5.0, 0, steps) == 1.0);

    steps = 0;
    assert(quickPower(5.0, 0, steps) == 1.0);

    calls = 0;
    assert(power_rec(5.0, 0, calls) == 1.0);

    calls = 0;
    assert(quickPower_rec(5.0, 0, calls) == 1.0);

    cout << "n = 0 test passed!" << endl;
}


// comparison amount of steps
void compareSteps()
{
    double x = 1.0001;
    unsigned int n = 1000000;

    unsigned long long powerSteps = 0;
    unsigned long long quickSteps = 0;

    power(x, n, powerSteps);
    quickPower(x, n, quickSteps);


    cout << endl;
    cout << "Step comparison:" << endl;

    cout << "n = " << n << endl;
    cout << "power steps = " << powerSteps << endl;
    cout << "quickPower steps = " << quickSteps << endl;
}


// comparison time
void compareTime()
{
    const double x = 1.0001;
    const unsigned int n = 10000;
    const int repetitions = 100;

    volatile double result = 0.0;

    auto start1 = chrono::high_resolution_clock::now();

    for (int i = 0; i < repetitions; ++i)
    {
        unsigned long long steps = 0;
        result += power(x, n, steps);
    }

    auto end1 = chrono::high_resolution_clock::now();

    auto start2 = chrono::high_resolution_clock::now();

    for (int i = 0; i < repetitions; ++i)
    {
        unsigned long long steps = 0;
        result += quickPower(x, n, steps);
    }

    auto end2 = chrono::high_resolution_clock::now();

    auto start3 = chrono::high_resolution_clock::now();

    for (int i = 0; i < repetitions; ++i)
    {
        unsigned long long calls = 0;
        result += power_rec(x, n, calls);
    }

    auto end3 = chrono::high_resolution_clock::now();

    auto start4 = chrono::high_resolution_clock::now();

    for (int i = 0; i < repetitions; ++i)
    {
        unsigned long long calls = 0;
        result += quickPower_rec(x, n, calls);
    }

    auto end4 = chrono::high_resolution_clock::now();

    auto time1 =
        chrono::duration_cast<chrono::microseconds>(end1 - start1);

    auto time2 =
        chrono::duration_cast<chrono::microseconds>(end2 - start2);

    auto time3 =
        chrono::duration_cast<chrono::microseconds>(end3 - start3);

    auto time4 =
        chrono::duration_cast<chrono::microseconds>(end4 - start4);

    cout << endl;
    cout << "Time comparison (" << repetitions
         << " repetitions):" << endl;

    cout << "power:          " << time1.count() << " us" << endl;
    cout << "quickPower:     " << time2.count() << " us" << endl;
    cout << "power_rec:      " << time3.count() << " us" << endl;
    cout << "quickPower_rec: " << time4.count() << " us" << endl;
}


int main()
{
    testCorrectness();

    cout << endl;

    testZeroPower();

    cout << endl;

    compareSteps();

    cout << endl;

    compareTime();

    return 0;
}