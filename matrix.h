#ifndef MATRIX_H
#define MATRIX_H

#include "TypeInfo.h"
#include "MatrixError.h"
#include <stdbool.h>

typedef struct {
	unsigned int order;
	void*** elements;
	Type_Info* type_Info;
} Matrix;

Matrix* Mtrx_create(Type_Info* type_Info, unsigned int order, Mtrx_error* code);

void Mtrx_fill(Matrix* mtrx, Mtrx_error* code);

void Mtrx_free(Matrix* mtrx);

void Mtrx_add(const Matrix* A, const Matrix* B, Matrix* C, Mtrx_error*code);

void Mtrx_multiply(const Matrix* A, const Matrix* B, Matrix* C, Mtrx_error*code);

void Mtrx_multiply_digit(Matrix* A, const double digit, Mtrx_error* code);

bool Mtrx_comparison(const Matrix* A, const Matrix* B, Mtrx_error* code);

void Mtrx_print(Matrix* mtrx, Mtrx_error* code);

#endif 