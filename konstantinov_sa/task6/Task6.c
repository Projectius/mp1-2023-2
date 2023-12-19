#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<math.h>

#define pi 3.14159265358979323846

unsigned long long ullFactorial(unsigned a) {
	unsigned long long r = 1;
	for (unsigned i = 2; i <= a;i++)
		r *= i;
	return r;
}

int minusOnePow(unsigned a) {
	return (a % 2) ? -1 : 1;
}

double argWrap(double arg, double period) {
	//int neg = minusOnePow(arg > 0);
	//arg = abs(arg);
	/*while (arg > period)
		arg -= period;*/
	int ps = arg / period;
	arg -= ps * period;
	return arg;
}

double partSin(double x, unsigned n) {
	x = argWrap(x, 2 * pi);
	int sig = (x < 0) ? -1 : 1;
	x *= sig;
	if (x > pi) {
		x -= pi;
		sig *= -1;
	}
	if (x > pi / 2) {
		x = pi - x;
	}
	return sig*minusOnePow(n) * pow(x, 2 * n + 1) / ullFactorial(2*n+1);
}

double tSin(double x, unsigned n) {
	x = argWrap(x, 2 * pi);
	int sig = (x < 0) ? -1 : 1;
	x *= sig;
	if (x > pi) {
		x -= pi;
		sig *= -1;
	}
	if (x > pi / 2) {
		x = pi - x;
	}
	double res = x;
	double term = x;
	for (int i = 1; i <= n; i++) {
		term *= -1 * x * x / ((2 * i) * (2 * i + 1));
		res += term;
	}

	return sig*res;
}

double sinArg(double x, int* sig) {
	x = argWrap(x, 2 * pi);
	int s = (x < 0) ? -1 : 1;
	x *= s;
	if (x > pi) {
		x -= pi;
		s *= -1;
	}
	if (x > pi / 2) {
		x = pi - x;
	}
	*sig = s;
	return x;
}

void tpSin(double x, unsigned n, double* term, double* ans) {
	if (n == 0) {
		*ans = x;
		*term = x;
	}
	else {
		*term *= -1 * x * x / ((2 * n) * (2 * n + 1));
		*ans += *term;
	}
	
}

void Taylor(double x, unsigned n) {
	double ans;
	double t;
	double e = sin(x);
	int sig;
	double sx = sinArg(x, &sig);
	for (unsigned i = 0; i < n;i++) {
		tpSin(sx, i, &t, &ans);
		
	
		printf("%lf %lf %lf < %lf\n",tSin(x, i), ans*sig, t, fabs(ans-e));
	}
	printf("%lf = Ethanol: ", e);
}

int main() {
	/*for (int i = 0; i <= 21;i++) {
		unsigned long long f = ullFactorial(i);
		printf("%llu %lf \n",f, (double)f );
	}*/

	Taylor(pi/2, 10);
	system("pause");
	return 0;
}