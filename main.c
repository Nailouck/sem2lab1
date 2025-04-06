#include <stdio.h>
#include <time.h>
#include "complex.h"
#include "matrix.h"
#include "MatrixError.h"
#include "test.h"
#include "interface.h"

//#define COMPLEX_TEST
//#define MATRIX_TEST_COMPLEX
//#define MATRIX_TEST_INTEGER
//#define MATRIX_TEST_SPECIAL

int main(int argc, char* argv[]) {
	srand(time(NULL));
	
#ifdef COMPLEX_TEST
	Cmplx_test();
#endif
	
#ifdef MATRIX_TEST_COMPLEX
	Mtrx_test_Complex();
#endif

#ifdef MATRIX_TEST_INTEGER
	Mtrx_test_Integer();
#endif

#ifdef MATRIX_TEST_SPECIAL
	Mtrx_test_special();
#endif

	Mtrx_error* code = (Mtrx_error*)malloc(sizeof(Mtrx_error));
	run(argc, argv, code);
	err_proc(code);
	free(code);
	
	return EXIT_SUCCESS;
}
