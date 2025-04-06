#ifndef TYPEINFO_H
#define TYPEINFO_H

#include <stdlib.h>
#include <stdbool.h>

typedef void* (*Binary_Operator)(const void* arg1, const void* arg2);

typedef struct {
	size_t size;
	size_t ptr_size;
	Binary_Operator add;
	Binary_Operator multiply;
	void* (*multiply_digit)(void* arg1, const double arg2);
	void (*print)(const void*);
	void (*scan)(void*);
	bool (*comparison)(const void* arg1, const void* arg2);
} Type_Info;

#endif