#ifndef MATRIXERROR_H
#define MATRIXERROR_H

typedef enum {
	MATRIX_OPERATION_OK = 0,
	MEMORY_ALLOCATION_FAILED = 100,
	INCOMPATIBLE_MATRIX_ORDERS = 200,
	INCOMPATIBLE_MATRIX_TYPES = 300,
	NULL_MATRIX_ORDER = 400,
	MEMORY_FREE_FAILED = 500,
	INCOMPATIBLE_ARRAY_ORDER = 600
} Mtrx_error;

void err_proc(Mtrx_error* code);

#endif