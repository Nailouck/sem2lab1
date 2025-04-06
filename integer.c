#include "integer.h"
#include "TypeInfo.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

void* int_add(const void* arg1, const void* arg2) {
	void* result;
	*(int*)(result) = *(int*)arg1 + *(int*)arg2;
	return result;
}

void* int_multiply(const void* arg1, const void* arg2) {
	void* result;
	*(int*)result = *(int*)arg1 * *(int*)arg2;
	return result;
}

void* int_multiply_digit(void* arg1, const double arg2) {
	*(int*)arg1 *= (int)arg2;
	return arg1;
}

void int_scan(void* arg1) { scanf("%d", (int*)arg1); }

void int_print(const void* arg1) { printf("%d", *(int*)arg1); }

bool int_comparison(const void* arg1, const void* arg2) { return *(int*)arg1 == *(int*)arg2 ? true : false; }


Type_Info* Get_int_type_info() {
	if (INT_TYPE_INFO == NULL) {
		INT_TYPE_INFO = (Type_Info*)malloc(sizeof(Type_Info));
		INT_TYPE_INFO->size = sizeof(int);
		INT_TYPE_INFO->ptr_size = sizeof(int*);
		INT_TYPE_INFO->add = int_add;
		INT_TYPE_INFO->multiply = int_multiply;
		INT_TYPE_INFO->multiply_digit = int_multiply_digit;
		INT_TYPE_INFO->scan = int_scan;
		INT_TYPE_INFO->print = int_print;
		INT_TYPE_INFO->comparison = int_comparison;
	}
	return INT_TYPE_INFO;
}

void Free_Int_type_Info() { free(INT_TYPE_INFO); }