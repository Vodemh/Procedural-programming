#ifndef POWER_H
#define POWER_H

double power(double x, unsigned int n, unsigned long long& steps);

double quickPower(double x, unsigned int n, unsigned long long& steps);

double power_rec(double x, unsigned int n, unsigned long long& calls);

double quickPower_rec(double x, unsigned int n, unsigned long long& calls);

#endif