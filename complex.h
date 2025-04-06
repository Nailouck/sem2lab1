#ifndef COMPLEX_H
#define COMPLEX_H

#include <stdbool.h>
#include "TypeInfo.h"

static Type_Info* COMPLEX_TYPE_INFO = NULL;

typedef struct {
	double Re;
	double Im;
} Complex;

void* Cmplx_add(const Complex* a, const Complex* b);
void* Cmplx_multiply(const Complex* a, const Complex* b);
void* Cmplx_multiply_digit(Complex* a, const double b);
bool Cmplx_comparison(const Complex* a, const Complex* b);
void Cmplx_scan(Complex* arg1);
void Cmplx_print(const Complex* a);

void* Cmplx_add_wrap(const void* arg1, const void* arg2);
void* Cmplx_multiply_wrap(const void* arg1, const void* arg2);
void* Cmplx_multiply_digit_wrap(void* arg1, const double arg2);
bool Cmplx_comparison_wrap(const void* arg1, const void* arg2);
void Cmplx_scan_wrap(void* arg1);
void Cmplx_print_wrap(const void* arg1);

Type_Info* Get_Cmplx_type_Info();

void Free_Cmplx_type_Info();

#endif