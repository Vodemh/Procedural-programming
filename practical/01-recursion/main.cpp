#include <iostream>
#include <cmath>
using namespace std;

#include "root.h"
#include "factorial.h"
#include "expoSum.h"
#include "chebyshev.h"

int main()
{
	const double two=2.0;
	const double prec = 0.000001;
	const int i = 10;

	double x;
    int n;

    cout << "Enter x: ";
    cin >> x;

    cout << "Enter n: ";
    cin >> n;


	cout.precision(27);
//	Try to set precision to 18 and compare the result
	cout << "The square root of 2 calculated with"<<endl
		<<" a standart fuction is " << sqrt(2.0) << endl;
	cout <<"      your function is "<< root(two,prec)<<endl;

	cout << "The factorial of 10 calculated with"<<endl
		<<"      your function is "<< factorial(i)<<endl;

    // First n sum
    double series = exponentialSeries(x, n);

    cout << "Sum of series = " << series << endl;

    cout << "exp(x) = " << exp(x) << endl;


    // Chebyshev
    cout << "Chebyshev T_" << n << "(x) = "
         << chebyshev(x, n) << endl;
	return 0;
}
