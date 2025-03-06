#include "integer.h"
#include "TypeInfo.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

void int_add(const int a, const int b, int* result) { *result = a + b; }

void int_multiply(const int a, const int b, int* result) { *result = a * b; }

void int_multiply_digit(int* a, const double b) { *a *= (int)b; }

void int_print(const int a) { printf("%d", a); }

bool int_compairson(const int a, const int b) { return a == b ? true : false; }

Type_Info* Get_int_type_info() {
	if (INT_TYPE_INFO == NULL) {
		INT_TYPE_INFO = (Type_Info*)malloc(sizeof(Type_Info));
		INT_TYPE_INFO->size = sizeof(int);
		INT_TYPE_INFO->ptr_size = sizeof(int*);
		INT_TYPE_INFO->add = int_add;
		INT_TYPE_INFO->multiply = int_multiply;
		INT_TYPE_INFO->multiply_digit = int_multiply_digit;
		INT_TYPE_INFO->print = int_print;
		INT_TYPE_INFO->compairson = int_compairson;
	}
	return INT_TYPE_INFO;
}