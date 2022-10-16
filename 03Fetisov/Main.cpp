#include <iostream>
#include <cmath>

using namespace std;

long double gauss(double);
long double exponent(double);
long double transPow(double, double);
long double root(double, int);
long double power(double, int);

const double e = 0.00001;

void main(void) {
	for (int i = -10; i <= 10; i++) {
		cout << "Gaussian integral: " << gauss(i) << endl;
		cout << "Exponent: " << exponent(i) << endl;
		cout << "Transformated Exp: " << transPow(exp(1), i) << endl;
		cout << "Exponent(cmath): " << pow(exp(1), i) << endl;
		cout << "" << endl;
	}
}
//Висновок: Некоректні результати обчислення для e^(-x^2) за розкладом в ряд після x = 6. 
//Некоректні результати обчислення для e^x за розкладом в ряд для x < 0. Причина - несумірність доданків.

long double gauss(double x) {
	long double a = x;
	long double res = x;
	unsigned int i = 1;
	while (fabs(a) > e) {	
		a *= -((x * x) * (2 * i - 1)) / ((2 * i + 1) * i);
		res += a;
		i++;
	}
	return res;
}

long double exponent(double x) {
	long double a = 1;
	long double res = 1;
	unsigned int i = 1;
	while (fabs(a) > e) {
		a *= x / i;
		res += a;
		i++;
	}
	return res;
}

long double transPow(double x, double n) {
	unsigned int denominator = 1;
	while (fabs(n) - (int)fabs(n) > e) {
		n *= 10;
		denominator *= 10;
	}
	if (n >= 0) {
		return root(power(x, n), denominator);
	}
	else {
		n *= -1;
		return 1 / root(power(x, n), denominator);
	}
}

long double power(double x, int n){
	double res = 1;
	for (int i = 1; i <= abs(n); i++) {
		res = res * x;
	}
	if (n < 0) {
		return 1 / res;
	}
	return res;
}

long double root(double x, int n){
	double prev_y, next_y;
	next_y = x;
	do {
		prev_y = next_y;
		next_y = (prev_y * (n - 1) + x / power(prev_y, n - 1)) / n;
	} while (fabs(next_y - prev_y) > e);
	return next_y;
}