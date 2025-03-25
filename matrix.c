#include "matrix.h"
#include "complex.h"
#include "integer.h"
#include "TypeInfo.h"
#include "MatrixError.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

Matrix* Mtrx_create(Type_Info* type_Info, unsigned int order, Mtrx_error* code) {
	
	//*code = MATRIX_OPERATION_OK;

	if (order == 0) {
		*code = NULL_MATRIX_ORDER;
		err_proc(code);
		return NULL;
	}

	Matrix* mtrx = (Matrix*)malloc(sizeof(Matrix));
	mtrx->order = order;

	if (mtrx == NULL) {
		*code = MEMORY_ALLOCATION_FAILED;
		err_proc(code);
		Mtrx_free(mtrx);
		return NULL;
	}

	mtrx->type_Info = type_Info;
	mtrx->elements = (void***)malloc(sizeof(void*) * order);
	for (unsigned int i = 0; i < order; i++) {
		mtrx->elements[i] = (void**)malloc(type_Info->size * order);
	}

	err_proc(code);
	return mtrx;
}

void Mtrx_fill(Matrix* mtrx) {
	for (size_t i = 0; i < mtrx->order; i++) {
		for (size_t j = 0; j < mtrx->order; j++) {
			mtrx->type_Info->scan(&mtrx->elements[i][j]);
		}
	}
}

void Mtrx_free(Matrix* mtrx) {
	for (int i = 0; i < mtrx->order; i++) {
		free(mtrx->elements[i]);
	}
	free(mtrx->elements);
	free(mtrx);
}

void Mtrx_add(const Matrix* A, const Matrix* B, Matrix* C, Mtrx_error* code) {
	if (A->type_Info != B->type_Info || C->type_Info != A->type_Info) {
		*code = INCOMPATIBLE_MATRIX_TYPES;
		err_proc(code);
		return;
	}
	if (C->order != A->order || A->order != B->order) {
		*code = INCOMPATIBLE_MATRIX_ORDERS;
		err_proc(code);
		return;
	}

	for (int i = 0; i < A->order; i++) {
		for (int j = 0; j < A->order; j++) {
			C->type_Info->add(&A->elements[i][j], &B->elements[i][j], &C->elements[i][j]);
		}
	}
	*code = MATRIX_OPERATION_OK;
	err_proc(code);
}

void Mtrx_multiply(const Matrix* A, const Matrix* B, Matrix* C, Mtrx_error*code) {
	if (C->order != A->order || A->order != B->order) {
		*code = INCOMPATIBLE_MATRIX_ORDERS;
		err_proc(code);
		return;
	}
	if (A->type_Info != B->type_Info) {
		*code = INCOMPATIBLE_MATRIX_TYPES;
		err_proc(code);
		return;
	}

	for (int i = 0; i < A->order; i++) {
		for (int j = 0; j < A->order; j++) {
			C->type_Info->add(&A->elements[j][i], &B->elements[i][j], &C->elements[i][j]);
		}
	}

	*code = MATRIX_OPERATION_OK;
	err_proc(code);
}

void Mtrx_multiply_digit(Matrix* A, const double digit) {
	for (int i = 0; i < A->order; i++) {
		for (int j = 0; j < A->order; j++) {
			A->type_Info->multiply_digit(&A->elements[i][j], digit);
		}
	}
}

bool Mtrx_comparison(const Matrix* A, const Matrix* B) {
	if (A->order != B->order) return false;
	for (int i = 0; i < A->order; i++) {
		for (int j = 0; j < A->order; j++) {
			if (A->type_Info->compairson(&A->elements[i][j], &B->elements[i][j]) == false) return false;
		}
	}
	return true;
}

Matrix* Mtrx_identity(Type_Info* type_Info, unsigned int order, Mtrx_error* code) {
	Matrix* mtrx = Mtrx_create(type_Info, order, code);

	if (*code != MATRIX_OPERATION_OK) { return NULL; }

	Complex one = { 1, 0 };
	Complex zero = { 0, 0 };

	switch (type_Info->size) {
		case sizeof(int) :
			for (int i = 0; i < order; i++) {
				for (int j = 0; j < order; j++) {
					*(int*)mtrx->elements[i][j] = (i == j ? 1 : 0);
				}
			}
			break;
		case sizeof(Complex) :
			for (int i = 0; i < order; i++) {
				for (int j = 0; j < order; j++) {
					*(Complex*)mtrx->elements[i][j] = (i == j ? one : zero);
				}
			}
			break;
	}
	return mtrx;
}

Matrix* Mtrx_zero(Type_Info* type_Info, unsigned int order, Mtrx_error* code) {
	Matrix* mtrx = Mtrx_create(type_Info, order, code);

	if (*code != MATRIX_OPERATION_OK) { return NULL; }

	Complex zero = { 0, 0 };

	switch (type_Info->size) {
		case sizeof(int) :
			for (int i = 0; i < order; i++) {
				for (int j = 0; j < order; j++) {
					*(int*)mtrx->elements[i][j] = 0;
				}
			}
		break;
		case sizeof(Complex) :
			for (int i = 0; i < order; i++) {
				for (int j = 0; j < order; j++) {
					*(Complex*)mtrx->elements[i][j] = zero;
				}
			}
		break;
	}
	return mtrx;
}

void Mtrx_print(Matrix* mtrx) {
	printf("{ ");
	for (size_t i = 0; i < mtrx->order; i++) {
		printf("{ ");
		for (size_t j = 0; j < mtrx->order; j++) {
			mtrx->type_Info->print(mtrx->elements[i][j]);
			if (j < mtrx->order - 1) printf(", ");
		}
		printf(" }");
	}
	printf(" }");
}