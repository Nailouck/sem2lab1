#include "matrix.h"
#include "complex.h"
#include "integer.h"
#include "TypeInfo.h"
#include "MatrixError.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
	mtrx->elements = (void***)malloc(sizeof(void**) * order);
	for (unsigned int i = 0; i < order; i++) {
		mtrx->elements[i] = (void**)malloc(type_Info->size * order);
		for (int j = 0; j < order; j++) {
			mtrx->elements[i][j] = malloc(type_Info->size);
		}
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
	if (mtrx == NULL) return;
	for (int i = 0; i < mtrx->order; i++) {
		if (mtrx->elements[i] == NULL) return;
		for (int j = 0; j < mtrx->order; j++) {
			if (mtrx->elements[i][j] == NULL) return;
			free(mtrx->elements[i][j]);
		}
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
			void* old = C->elements[i][j];
			C->elements[i][j] = C->type_Info->add(&A->elements[i][j], &B->elements[i][j]);
			if (old != NULL) free(old);
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
			for (int k = 0; k < A->order; k++) {
				void* old = C->elements[i][j];
				if (k == 0) C->elements[i][j] = C->type_Info->multiply(&A->elements[i][k], &B->elements[k][i]);
				else C->elements[i][j] = C->type_Info->add(C->type_Info->multiply(&A->elements[i][k], &B->elements[k][j]), &C->elements[i][j]);
				if (old != NULL) free(old);
			}
		}
	}
	
	*code = MATRIX_OPERATION_OK;

	err_proc(code);
}

void Mtrx_multiply_digit(Matrix* A, const double digit) {
	for (int i = 0; i < A->order; i++) {
		for (int j = 0; j < A->order; j++) {
			void* old = A->elements[i][j];
			A->elements[i][j] = A->type_Info->multiply_digit(&A->elements[i][j], digit);
			if (old != NULL) free(old);
		}
	}
}

bool Mtrx_comparison(const Matrix* A, const Matrix* B) {
	if (A->order != B->order) return false;
	for (int i = 0; i < A->order; i++) {
		for (int j = 0; j < A->order; j++) {
			if (A->type_Info->comparison(&A->elements[i][j], &B->elements[i][j]) == false) return false;
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