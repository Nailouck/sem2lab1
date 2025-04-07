#include "MatrixError.h"
#include <stdio.h>

void err_proc(Mtrx_error* code) {
    switch (*code) {
    case MATRIX_OPERATION_OK: {
        break;
    }
    case MEMORY_ALLOCATION_FAILED: {
        printf("MEMORY ALLOCATION FAILED! Error code 100\n");
        break;
    }
    case INCOMPATIBLE_MATRIX_ORDERS: {
        printf("INCOMPATIBLE MATRIX ORDERS! Error code 200\n");
        break;
    }
    case INCOMPATIBLE_MATRIX_TYPES: {
        printf("INCOMPATIBLE MATRIX TYPES! Error code 300\n");
        break;
    }
    case NULL_MATRIX_ORDER: {
        printf("NULL MATRIX ORDER! Error code 400\n");
        break;
    }
    case MEMORY_FREE_FAILED: {
        printf("MEMORY FREE FAILED! Error code 500\n");
        break;
    }
    case INCOMPATIBLE_ARRAY_ORDER: {
        printf("INCOMPATIBLE ARRAY ORDER! Error code 600\n");
        break;
    }
    case MATRIX_OPERATION_FAILED: {
        printf("MATRIX OPERATION FAILED! Error code 700\n");
        break;
    }
    case NULL_MATRIX: {
        printf("NULL-MATRIX has been encountered! Error code 800\n");
        break;
    }
    }
}