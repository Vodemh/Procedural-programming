#include <cmath>

double root (double x, double eps)
{
	double s=0.5*x;
	double t;
	do
	{
		t=s;
		s=(s+x/s)*0.5;
	}
	while ((fabs(s-t)/s)>eps);
	return s;
};
