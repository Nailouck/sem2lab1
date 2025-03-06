#include <stdio.h>
#include "complex.h"
#include "matrix.h"
#include "test.h"

int main() {
	srand(time(NULL));
	Complex arr[3][3] = {
		{{1, 2}, {2, 3}, {3, 4}},
		{{4, 5}, {5, 6}, {6, 7}},
		{{7, 8}, {8, 9}, {9, 0}}
	};
	unsigned int order = 3;
	Matrix_errors* code;
	Matrix* mtrx = create_Matrix(Get_Cmplx_type_Info(), arr, &code, order);

	if (*code != MATRIX_OPERATION_OK) printf("Err\n");
	free_Matrix(mtrx, &code);
	if (*code != MATRIX_OPERATION_OK) printf("Err\n");
	return 0;
}
