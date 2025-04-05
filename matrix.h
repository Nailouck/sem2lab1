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

void Mtrx_fill(Matrix* mtrx);

void Mtrx_free(Matrix* mtrx);

void Mtrx_add(const Matrix* A, const Matrix* B, Matrix* C, Mtrx_error*code);

void Mtrx_multiply(const Matrix* A, const Matrix* B, Matrix* C, Mtrx_error*code);

void Mtrx_multiply_digit(Matrix* A, const double digit);

bool Mtrx_comparison(const Matrix* A, const Matrix* B);

//Matrix* Mtrx_identity(Type_Info* type_Info, unsigned int order, Mtrx_error* code);

//Matrix* Mtrx_zero(Type_Info* type_Info, unsigned int order, Mtrx_error* code);

void Mtrx_print(Matrix* mtrx);

#endif 