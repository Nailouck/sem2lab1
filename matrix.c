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
    if (!mtrx) {
        *code = MEMORY_ALLOCATION_FAILED;
        err_proc(code);
        return NULL;
    }

    mtrx->order = order;
    mtrx->type_Info = type_Info;
    
    mtrx->elements = (void***)malloc(sizeof(void**) * order);
    if (!mtrx->elements) {
        free(mtrx);
        *code = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }

    for (unsigned int i = 0; i < order; i++) {
        mtrx->elements[i] = (void**)malloc(sizeof(void*) * order);
        if (!mtrx->elements[i]) {
            for (unsigned int k = 0; k < i; k++) free(mtrx->elements[k]);
            free(mtrx->elements);
            free(mtrx);
            *code = MEMORY_ALLOCATION_FAILED;
            return NULL;
        }
        
        for (unsigned int j = 0; j < order; j++) {
            mtrx->elements[i][j] = malloc(type_Info->size);
            if (!mtrx->elements[i][j]) {
                for (unsigned int k = 0; k < j; k++) free(mtrx->elements[i][k]);
                free(mtrx->elements[i]);
                for (unsigned int k = 0; k < i; k++) {
                    for (unsigned int l = 0; l < order; l++) free(mtrx->elements[k][l]);
                    free(mtrx->elements[k]);
                }
                free(mtrx->elements);
                free(mtrx);
                *code = MEMORY_ALLOCATION_FAILED;
                return NULL;
            }
            
            if (type_Info == Get_Cmplx_type_Info()) {
                Complex* zero = (Complex*)mtrx->elements[i][j];
                zero->Re = 0.0;
                zero->Im = 0.0;
            }
			else {
				int* zero = (int*)mtrx->elements[i][j];
				*zero = 0;
			}
        }
    }
    
    *code = MATRIX_OPERATION_OK;
    return mtrx;
}

void Mtrx_fill(Matrix* mtrx, Mtrx_error* code) {
    if (mtrx == NULL) {
        *code = NULL_MATRIX;
        err_proc(code);
        return;
    }
    printf("Write %d number(s) - elements of matrix.\n", mtrx->order * mtrx->order);
	for (size_t i = 0; i < mtrx->order; i++) {
        if (mtrx->elements[i] == NULL) {
            *code = NULL_MATRIX;
            err_proc(code);
            return;
        }
		for (size_t j = 0; j < mtrx->order; j++) {
            if (mtrx->elements[i][j] == NULL) {
                *code = NULL_MATRIX;
                err_proc(code);
                return;
            }
			mtrx->type_Info->scan(mtrx->elements[i][j]);
		}
	}
    *code = MATRIX_OPERATION_OK;
}

void Mtrx_free(Matrix* mtrx) {
	if (mtrx == NULL) return;
	for (int i = 0; i < mtrx->order; i++) {
		if (mtrx->elements[i] == NULL) continue;
		for (int j = 0; j < mtrx->order; j++) {
			if (mtrx->elements[i][j] == NULL) continue;
			free(mtrx->elements[i][j]);
		}
		free(mtrx->elements[i]);
	}
	free(mtrx->elements);
	free(mtrx);
}

void Mtrx_add(const Matrix* A, const Matrix* B, Matrix* C, Mtrx_error* code) {
    if (A->elements == NULL || B->elements == NULL) {
        *code = NULL_MATRIX;
        err_proc(code);
        return;
    }
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
        if (A->elements[i] == NULL || B->elements[i] == NULL) {
            *code = NULL_MATRIX;
            err_proc(code);
            return;
        }
		for (int j = 0; j < A->order; j++) {
            if (A->elements[i][j] == NULL || B->elements[i][j] == NULL) {
                *code = NULL_MATRIX;
                err_proc(code);
                return;
            }
			void* old = C->elements[i][j];
			C->elements[i][j] = C->type_Info->add(A->elements[i][j], B->elements[i][j]);
			if (old != NULL) free(old);
		}
	}
	*code = MATRIX_OPERATION_OK;
}

void Mtrx_multiply(const Matrix* A, const Matrix* B, Matrix* C, Mtrx_error* code) {
    if (A->elements == NULL || B->elements == NULL) {
        *code = NULL_MATRIX;
        err_proc(code);
        return;
    }
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
        if (A->elements[i] == NULL) {
            *code = NULL_MATRIX;
                    err_proc(code);
                    return;
        }
        for (int j = 0; j < A->order; j++) {
            void* sum = NULL;
            
            for (int k = 0; k < A->order; k++) {
                if (B->elements[k] == NULL || B->elements[k][j] == NULL || A->elements[i][k] == NULL) {
                    *code = NULL_MATRIX;
                    err_proc(code);
                    return;
                }
                void* result = C->type_Info->multiply(A->elements[i][k], B->elements[k][j]);
                
                if (k == 0) {
                    sum = result;
                } else {
                    void* new_sum = C->type_Info->add(sum, result);
                    free(sum);
                    free(result);
                    sum = new_sum;
                }
            }
            free(C->elements[i][j]);
            C->elements[i][j] = sum;
        }
    }
    
    *code = MATRIX_OPERATION_OK;
}

void Mtrx_multiply_digit(Matrix* A, const double digit, Mtrx_error* code) {
    if (A->elements == NULL) {
        *code = NULL_MATRIX;
                err_proc(code);
                return;
    }

	for (int i = 0; i < A->order; i++) {
        if (A->elements[i] == NULL) {
            *code = NULL_MATRIX;
                err_proc(code);
                return;
        }
		for (int j = 0; j < A->order; j++) {
            if (A->elements[i][j] == NULL) {
                *code = NULL_MATRIX;
                err_proc(code);
                return;
            }
			void* old = A->elements[i][j];
			A->elements[i][j] = A->type_Info->multiply_digit(A->elements[i][j], digit);
		}
	}
    *code = MATRIX_OPERATION_OK;
}

bool Mtrx_comparison(const Matrix* A, const Matrix* B, Mtrx_error* code) {
    if (A->elements == NULL || B->elements == NULL) {
        *code = NULL_MATRIX;
                err_proc(code);
                return false;
    }

	if (A->order != B->order) return false;
	for (int i = 0; i < A->order; i++) {
        if (A->elements[i] == NULL || B->elements[i] == NULL) {
            *code = NULL_MATRIX;
                err_proc(code);
                return false;
        }
		for (int j = 0; j < A->order; j++) {
            if (A->elements[i][j] == NULL || B->elements[i][j] == NULL) {
                *code = NULL_MATRIX;
                err_proc(code);
                return false;
            }
            *code = MATRIX_OPERATION_OK;
			if (A->type_Info->comparison(A->elements[i][j], B->elements[i][j]) == false) return false;
		}
	}
	return true;
}

void Mtrx_print(Matrix* mtrx, Mtrx_error* code) {
    if (mtrx->elements == NULL) {
        *code = NULL_MATRIX;
            err_proc(code);
            return;
    }
	printf("{");
	for (size_t i = 0; i < mtrx->order; i++) {
        if (mtrx->elements[i] == NULL) {
            *code = NULL_MATRIX;
                err_proc(code);
                return;
        }
		printf("\t{\t");
		for (size_t j = 0; j < mtrx->order; j++) {
            if (mtrx->elements[i][j] == NULL) {
                *code = NULL_MATRIX;
                    err_proc(code);
                    return;
            }
			mtrx->type_Info->print(mtrx->elements[i][j]);
			if (j < mtrx->order - 1) printf(",\t");
		}
		if (i < mtrx->order - 1) printf("\t}\n");
	}
	printf("\t}\t}\n");
    *code = MATRIX_OPERATION_OK;
}