#include "complex.h"
#include "TypeInfo.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void Cmplx_add(const Complex a, const Complex b, Complex* result) {
	result->Re = a.Re + b.Re;
	result->Im = a.Im + b.Im;
}

void Cmplx_multiply(const Complex a, const Complex b, Complex* result) {
	result->Re = a.Re * b.Re - a.Im * b.Im;
	result->Im = a.Im * b.Re + a.Re * b.Im;
}

void Cmplx_multiply_digit(Complex* a, const double b) {
	a->Re *= b;
	a->Im *= b;
}

bool Cmplx_comparison(const Complex a, const Complex b) { return (a.Re == b.Re && a.Im == b.Im) ? true : false; }

void Cmplx_print(const Complex a) { printf("(%lf, %lf) ", a.Re, a.Im); }

Type_Info* Get_Cmplx_type_Info() {
	if (COMPLEX_TYPE_INFO == NULL) {
		COMPLEX_TYPE_INFO = (Type_Info*)malloc(sizeof(Type_Info));
		COMPLEX_TYPE_INFO->size = sizeof(Complex);
		COMPLEX_TYPE_INFO->ptr_size = sizeof(Complex*);
		COMPLEX_TYPE_INFO->add = Cmplx_add;
		COMPLEX_TYPE_INFO->multiply = Cmplx_multiply;
		COMPLEX_TYPE_INFO->multiply_digit = Cmplx_multiply_digit;
		COMPLEX_TYPE_INFO->print = Cmplx_print;
		COMPLEX_TYPE_INFO->compairson = Cmplx_comparison;
	}
	return COMPLEX_TYPE_INFO;
}