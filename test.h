#ifndef TEST_H
#define TEST_H

#include "complex.h"
#include <assert.h>
#include <stdio.h>

void cmplx_test() {
	Complex arg1;
	Complex arg2;
	Complex* result;
	Complex answer;
	for (int i = 0; i < 20; i++) {
		int r1 = rand() % 100, r2 = rand() % 100, i1 = rand() % 100, i2 = rand() % 100;
		arg1.Re = (double)r1;
		arg1.Im = (double)i1;
		arg2.Re = (double)r2;
		arg2.Im = (double)i2;

		Cmplx_add(arg1, arg2, result);
		answer.Re = (double)r1 + (double)r2;
		answer.Im = (double)i1 + (double)i2;
		printf("Integer addition (%lf, %lf) and (%lf, %lf). Expected value (%lf, %lf); Real value (%lf, %lf)\n", arg1.Re, arg1.Im, arg2.Re, arg2.Im, answer.Re, answer.Im, result->Re, result->Im);
		assert(Cmplx_comparison(*result, answer));

		Cmplx_multiply(arg1, arg2, result);
		answer.Re = (double)r1 * (double)r2 - (double)i1 * (double)i2;
		answer.Im = (double)i1 * (double)r2 + (double)r1 * (double)i2;
		printf("Integer multiplication (%lf, %lf) and (%lf, %lf). Expected value (%lf, %lf); Real value (%lf, %lf)\n", arg1.Re, arg1.Im, arg2.Re, arg2.Im, answer.Re, answer.Im, result->Re, result->Im);
		assert(Cmplx_comparison(*result, answer));

		int r3 = (rand() % 1000);
		int r4 = (rand() % 1000);
		int i3 = (rand() % 1000);
		int i4 = (rand() % 1000);
		arg1.Re = (double)r3 / 10;
		arg1.Im = (double)i3 / 10;
		arg2.Re = (double)r4 / 10;
		arg2.Im = (double)i4 / 10;

		Cmplx_add(arg1, arg2, result);
		answer.Re = (double)(r3 + r4) / 10;
		answer.Im = (double)(i3 + i4) / 10;
		printf("Double addition (%lf, %lf) and (%lf, %lf). Expected value (%lf, %lf); Real value (%lf, %lf)\n", arg1.Re, arg1.Im, arg2.Re, arg2.Im, answer.Re, answer.Im, result->Re, result->Im);
		assert(Cmplx_comparison(*result, answer));

		Cmplx_multiply(arg1, arg2, result);
		answer.Re = (double)r3 / 10 * (double)r4 / 10 - (double)i3 / 10 * (double)i4 / 10;
		answer.Im = (double)i3 / 10 * (double)r4 / 10 + (double)r3 / 10 * (double)i4 / 10;
		printf("Double multiplication (%lf, %lf) and (%lf, %lf). Expected value (%lf, %lf); Real value (%lf, %lf)\n", arg1.Re, arg1.Im, arg2.Re, arg2.Im, answer.Re, answer.Im, result->Re, result->Im);
		assert(Cmplx_comparison(*result, answer));
	}
}

#endif