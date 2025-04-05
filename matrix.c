#include "matrix.h"
#include "complex.h"
#include "integer.h"
#include "TypeInfo.h"
#include "MatrixError.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int NMAX = 3;

Matrix* Mtrx_create(Type_Info* type_Info, unsigned int order, Mtrx_error* code) {

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

	*code = MATRIX_OPERATION_OK;

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

	void* arr[NMAX];

	for (int i = 0; i < A->order; i++) { // Цикл по i и j изначально неправильный: он считает только диагональные элементы. Пере5писать индексацию, также продумать индексы в результирующей матрице.
		for (int j = 0; j < A->order; j++) {

			C->type_Info->multiply(&A->elements[i][j], &B->elements[j][i], &arr[j]);

			for (int k = 0; k < NMAX; k++) {
				if (k == 0) {
					C->type_Info->add(arr[k], arr[k + 1], C->elements[index1][index2]);
					k++;
				}
				C->type_Info->add(C->elements[index1][index2], arr[k], C->elements[index1][index2]);
			}
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

void Mtrx_print(Matrix* mtrx) {
	printf("{");
	for (size_t i = 0; i < mtrx->order; i++) {
		printf("\t{ ");
		for (size_t j = 0; j < mtrx->order; j++) {
			mtrx->type_Info->print(&mtrx->elements[i][j]);
			if (j < mtrx->order - 1) printf(", ");
		}
		if (i < mtrx->order - 1) printf(" }\n");
	}
	printf(" } }");
}