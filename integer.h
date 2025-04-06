#ifndef INTEGER_H
#define INTEGER_H

#include "TypeInfo.h"
#include <stdbool.h>

static Type_Info* INT_TYPE_INFO = NULL;

void* int_add(const void* arg1, const void* arg2);
void* int_multiply(const void* arg1, const void* arg2);
void* int_multiply_digit(void* arg1, const double arg2);
void int_scan(void* arg1);
void int_print(const void* arg1);
bool int_comparison(const void* arg1, const void* arg2);

Type_Info* Get_int_type_info();

void Free_Int_type_Info();

#endif