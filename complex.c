#include "complex.h"
#include "TypeInfo.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define NORMALYZING_COEF 1000000

void* Cmplx_add(const Complex* a, const Complex* b) {
	Complex* result = (Complex*)malloc(sizeof(Complex));
	result->Re = a->Re + b->Re;
	result->Im = a->Im + b->Im;
	return result;
}

void* Cmplx_multiply(const Complex* a, const Complex* b) {
	Complex* result = (Complex*)malloc(sizeof(Complex));
	result->Re = a->Re * b->Re - a->Im * b->Im;
	result->Im = a->Im * b->Re + a->Re * b->Im;
	return result;
}

void* Cmplx_multiply_digit(Complex* a, const double b) {
	void* result;
	a->Re *= b;
	a->Im *= b;
	result = a;
	return result;
}

bool Cmplx_comparison(const Complex* a, const Complex* b) { return ((int)(a->Re * NORMALYZING_COEF) == (int)(b->Re * NORMALYZING_COEF) && (int)(a->Im * NORMALYZING_COEF) == (int)(b->Im * NORMALYZING_COEF)) ? true : false; }

void Cmplx_scan(Complex* arg1) {
	scanf("%lf", &(arg1->Re));
	scanf("%lf", &(arg1->Im));
}

void Cmplx_print(const Complex* a) { printf("(%lf, %lf)", a->Re, a->Im); }



void* Cmplx_add_wrap(const void* arg1, const void* arg2) {
	return Cmplx_add((Complex*)(arg1), (Complex*)(arg2));
}

void* Cmplx_multiply_wrap(const void* arg1, const void* arg2) {
	return Cmplx_multiply((Complex*)(arg1), (Complex*)(arg2));
}

void* Cmplx_multiply_digit_wrap(void* arg1, const double arg2) {
	return Cmplx_multiply_digit((Complex*)(arg1), arg2);
}

void Cmplx_scan_wrap(void* arg1) { Cmplx_scan((Complex*)(arg1)); }

void Cmplx_print_wrap(const void* arg1) { Cmplx_print((Complex*)(arg1)); }

bool Cmplx_comparison_wrap(const void* arg1, const void* arg2) { return Cmplx_comparison((Complex*)(arg1), (Complex*)(arg2)); }


Type_Info* Get_Cmplx_type_Info() {
	if (COMPLEX_TYPE_INFO == NULL) {
		COMPLEX_TYPE_INFO = (Type_Info*)malloc(sizeof(Type_Info));
		COMPLEX_TYPE_INFO->size = sizeof(Complex);
		COMPLEX_TYPE_INFO->ptr_size = sizeof(Complex*);
		COMPLEX_TYPE_INFO->add = Cmplx_add_wrap;
		COMPLEX_TYPE_INFO->multiply = Cmplx_multiply_wrap;
		COMPLEX_TYPE_INFO->multiply_digit = Cmplx_multiply_digit_wrap;
		COMPLEX_TYPE_INFO->scan = Cmplx_scan_wrap;
		COMPLEX_TYPE_INFO->print = Cmplx_print_wrap;
		COMPLEX_TYPE_INFO->comparison = Cmplx_comparison_wrap;
	}
	return COMPLEX_TYPE_INFO;
}

void Free_Cmplx_type_Info() { free(COMPLEX_TYPE_INFO); }