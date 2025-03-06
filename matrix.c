#include "matrix.h"
#include "TypeInfo.h"
#include "MatrixError.h"
#include <stdlib.h>
#include <stdbool.h>

Matrix* create_Matrix(Type_Info* type_Info, void*** arr, Matrix_errors* code, unsigned int order) {
	if (order == 0) {
		*code = NULL_MATRIX_ORDER;
		return NULL;
	}

	Matrix* mtrx = (Matrix*)malloc(sizeof(Matrix));

	if (mtrx == NULL) {
		*code = MEMORY_ALLOCATION_FAILED;
		return NULL;
	}

	for (int i = 0; i < order * type_Info->size; i += type_Info->size) {
		for (int j = 0; j < type_Info->size; j += type_Info->size) {
			if (*(arr + i) + j == NULL) {
				*code = INCOMPATIBLE_ARRAY_ORDER;
				return NULL;
			}
		}
	}

	mtrx->type_Info = type_Info;
	mtrx->elements = malloc(type_Info->ptr_size * order);
	for (unsigned int i = 0; i < order; i++) {
		mtrx->elements[i] = malloc(type_Info->size * order);
	}

	for (unsigned int i = 0; i < order; i++) {
		for (unsigned int j = 0; j < order; j++) {
			memcpy(mtrx->elements[i][j], arr[i][j], type_Info->size); // length(arr) == order
		}
	}

	*code = MATRIX_OPERATION_OK;
	return mtrx;
}

void free_Matrix(Matrix* mtrx, Matrix_errors *code) {
	for (int i = 0; i < mtrx->order; i++) {
		free(mtrx->elements[i]);
	}
	free(mtrx->elements);
	free(mtrx);
	*code = (mtrx->elements != NULL || mtrx != NULL) ? MEMORY_FREE_FAILED : MATRIX_OPERATION_OK;
}

void Mtrx_add(const Matrix A, const Matrix B, Matrix* C, Matrix_errors *code) {
	if (A.type_Info != B.type_Info || C->type_Info != A.type_Info) {
		*code = INCOMPATIBLE_MATRIX_TYPES;
		return;
	}
	if (C->order != A.order || A.order != B.order) {
		*code = INCOMPATIBLE_MATRIX_ORDERS;
		return;
	}

	for (int i = 0; i < A.order; i++) {
		for (int j = 0; j < A.order; i++) {
			C->type_Info->add(A.elements[i][j], B.elements[i][j], &C->elements[i][j]);
		}
	}
	*code = MATRIX_OPERATION_OK;
}

void Mtrx_multiply(const Matrix A, const Matrix B, Matrix* C, Matrix_errors *code) {
	if (C->order != A.order || A.order != B.order) {
		*code = INCOMPATIBLE_MATRIX_ORDERS;
		return;
	}
	if (A.type_Info != B.type_Info) {
		*code = INCOMPATIBLE_MATRIX_TYPES;
		return;
	}

	for (int i = 0; i < A.order; i++) {
		for (int j = 0; j < A.order; j++) {
			C->type_Info->add(A.elements[j][i], B.elements[i][j], &C->elements[i][j]);
		}
	}

	*code = MATRIX_OPERATION_OK;
}

void Mtrx_multiply_digit(Matrix* A, const double digit) {
	for (int i = 0; i < A->order; i++) {
		for (int j = 0; j < A->order; j++) {
			A->type_Info->multiply_digit(A->elements[i][j], digit);
		}
	}
}

bool Mtrx_comparison(const Matrix A, const Matrix B) {
	if (A.order != B.order) return false;
	for (int i = 0; i < A.order; i++) {
		for (int j = 0; j < A.order; j++) {
			if (A.elements[i][j] != B.elements[i][j]) return false;
		}
	}
	return true;
}