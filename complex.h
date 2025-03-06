#ifndef COMPLEX_H
#define COMPLEX_H

#include <stdbool.h>
#include "TypeInfo.h"

static Type_Info* COMPLEX_TYPE_INFO = NULL;

typedef struct {
	double Re;
	double Im;
} Complex;

void Cmplx_add(const Complex a, const Complex b, Complex* result);

void Cmplx_multiply(const Complex a, const Complex b, Complex* result);

void Cmplx_multiply_digit(Complex* a, const double b);

bool Cmplx_comparison(const Complex a, const Complex b);

void Cmplx_print(const Complex a);

Type_Info* Get_Cmplx_type_Info();

#endif