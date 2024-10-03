// stdafx.cpp : source file that includes just the standard includes
// Example5.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// Code modification
double calculate_loss(double real, double imag) {
	double magnitude = sqrt(real * real + imag * imag);
	if (magnitude == 0.0)
		return 0.0;
	return -20.0 * log10(magnitude);
}
// ...

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

// Without using the standard library #include <cmath>
/*
double custom_sqrt(double value) {
	if (value <= 0.0)
		return 0.0;
	double guess = value;
	double epsilon = 0.000001;

	while ((guess * guess - value) > epsilon || (guess * guess - value) < -epsilon) {
		guess = (guess + value / guess) / 2.0;
	}
	
	return guess;
}

double custom_log10(double value) {
	if (value <= 0.0)
		return 0.0;

	double result = 0.0;
	double base = 10.0;

	while (value < 1.0) {
		value *= base;
		result -= 1.0;
	}

	while (value >= base) {
		value /= base;
		result += 1.0;
	}

	double frac = (value - 1) / (value + 1);
	double frac_squared = frac * frac;
	double term = frac;
	double numerator = 1.0;

	for (int i = 1; i < 10; i += 2) {
		result += term / numerator;
		term *= frac_squared;
		numerator += 2.0;
	}

	return result * 2.302585092994046;
}

double calculate_loss(double real, double imag) {
	double magnitude = custom_sqrt(real * real + imag * imag);
	if (magnitude == 0.0)
		return 0.0;
	return -20.0 * custom_log10(magnitude);
}
*/

// Fast approximations to speed up the calculation of the logarithm
// Note!: This method may be less accurate, but faster.
/*
float fast_sqrt(float x) {
	float xhalf = 0.5f * x;
	int i = *(int*)&x;
	i = 0x5f3759df - (i >> 1);
	x = *(float*)&i;
	x = x * (1.5f - xhalf * x * x);
	return 1.0f / x;
}

void custom_frexp(double value, int* exp, double* mantissa) {
	*exp = 0;
	*mantissa = value;
	
	if (value != 0.0) {
		while (*mantissa >= 1.0) {
			*mantissa /= 2.0;
			(*exp)++;
		}
		while (*mantissa < 0.5) {
			*mantissa *= 2.0;
			(*exp)--;
		}
	}
}

double fast_log10(double x) {
	int e;
	double m;

	custom_frexp(x, &e, &m);
	double log2 = e + m - 1;
	return log2 * 0.30102999566;
}

double calculate_loss(double real, double imag) {
	double magnitude = fast_sqrt(real * real + imag * imag);
	if (magnitude == 0.0)
		return 0.0;
	return -20.0 * fast_log10(magnitude);
}
*/
