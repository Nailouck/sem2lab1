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

Matrix* create_Matrix(Type_Info* type_Info, void*** arr, Matrix_errors* code, unsigned int order);

void free_Matrix(Matrix* mtrx, Matrix_errors *code);

void Mtrx_add(const Matrix A, const Matrix B, Matrix* C, Matrix_errors *code);

void Mtrx_multiply(const Matrix A, const Matrix B, Matrix* C, Matrix_errors *code);

void Mtrx_multiply_digit(Matrix* A, const double digit);

bool Mtrx_comparison(const Matrix A, const Matrix B);

#endif 