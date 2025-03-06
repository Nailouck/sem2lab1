#ifndef INTEGER_H
#define INTEGER_H

#include "TypeInfo.h"
#include <stdbool.h>

static Type_Info* INT_TYPE_INFO = NULL;

void int_add(const int a, const int b, int* result);

void int_multiply(const int a, const int b, int* result);

void int_multiply_digit(int* a, const double b);

void int_print(const int a);

bool int_compairson(const int a, const int b);

Type_Info* Get_int_type_info();

#endif