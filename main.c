#include <stdio.h>
#include <time.h>
#include "complex.h"
#include "matrix.h"
#include "test.h"
//#include "menu.h"

//#define COMPLEX_TEST
#define MATRIX_TEST

int main(int argc, char* argv[]) {
	srand(time(NULL));
	
#ifdef COMPLEX_TEST
	Cmplx_test();
#endif
	
#ifdef MATRIX_TEST
	Mtrx_test();
#endif

	//run(argc, argv);
	
	return EXIT_SUCCESS;
}
