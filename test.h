#ifndef TEST_H
#define TEST_H

#include "complex.h"
#include "integer.h"
#include "matrix.h"
#include <assert.h>
#include <stdio.h>
#include "MatrixError.h"



void Cmplx_test() {
	Complex arg1;
	Complex arg2;
	Complex result;
	Complex answer;
	for (int i = 0; i < 20; i++) {
		arg1.Re = (double)(rand() % 100);
		arg1.Im = (double)(rand() % 100);
		arg2.Re = (double)(rand() % 100);
		arg2.Im = (double)(rand() % 100);
		double digit = (double)(rand() % 100);

		answer.Re = arg1.Re + arg2.Re;
		answer.Im = arg1.Im + arg2.Im;
		Cmplx_add(&arg1, &arg2, &result);

		Cmplx_print(&arg1);
		Cmplx_print(&arg2);
		Cmplx_print(&answer);
		Cmplx_print(&result);

		printf("Integer addition (%lf, %lf) and (%lf, %lf). Expected value (%lf, %lf); Real value (%lf, %lf)\n", arg1.Re, arg1.Im, arg2.Re, arg2.Im, answer.Re, answer.Im, result.Re, result.Im);
		assert(Cmplx_comparison(&result, &answer));

		answer.Re = arg1.Re * arg2.Re - arg1.Im * arg2.Im;
		answer.Im = arg1.Im * arg2.Re + arg1.Re * arg2.Im;
		Cmplx_multiply(&arg1, &arg2, &result);

		Cmplx_print(&arg1);
		Cmplx_print(&arg2);
		Cmplx_print(&answer);
		Cmplx_print(&result);

		printf("Integer multiplication (%lf, %lf) and (%lf, %lf). Expected value (%lf, %lf); Real value (%lf, %lf)\n", arg1.Re, arg1.Im, arg2.Re, arg2.Im, answer.Re, answer.Im, result.Re, result.Im);
		assert(Cmplx_comparison(&result, &answer));

		answer.Re = arg1.Re * digit;
		answer.Im = arg1.Im * digit;
		printf("Integer multiplication (%lf, %lf) on digit %lf. ", arg1.Re, arg1.Im, digit);
		Cmplx_multiply_digit(&arg1, digit);
		printf("Expected value (%lf, %lf); Real value (%lf, %lf)\n", answer.Re, answer.Im, arg1.Re, arg1.Im);
		assert(Cmplx_comparison(&arg1, &answer));

		answer.Re = arg2.Re * digit;
		answer.Im = arg2.Im * digit;
		printf("Integer multiplication (%lf, %lf) on digit %lf. ", arg2.Re, arg2.Im, digit);
		Cmplx_multiply_digit(&arg2, digit);
		printf("Expected value (%lf, %lf); Real value (%lf, %lf)\n", answer.Re, answer.Im, arg2.Re, arg2.Im);
		assert(Cmplx_comparison(&arg2, &answer));


		arg1.Re = (double)(rand() % 1000) / 10;
		arg1.Im = (double)(rand() % 1000) / 10;
		arg2.Re = (double)(rand() % 1000) / 10;
		arg2.Im = (double)(rand() % 1000) / 10;
		digit = (double)(rand() % 1000) / 100;

		answer.Re = arg1.Re + arg2.Re;
		answer.Im = arg1.Im + arg2.Im;
		Cmplx_add(&arg1, &arg2, &result);

		Cmplx_print(&arg1);
		Cmplx_print(&arg2);
		Cmplx_print(&answer);
		Cmplx_print(&result);

		printf("Double addition (%lf, %lf) and (%lf, %lf). Expected value (%lf, %lf); Real value (%lf, %lf)\n", arg1.Re, arg1.Im, arg2.Re, arg2.Im, answer.Re, answer.Im, result.Re, result.Im);
		assert(Cmplx_comparison(&result, &answer));

		answer.Re = arg1.Re * arg2.Re - arg1.Im * arg2.Im;
		answer.Im = arg1.Im * arg2.Re + arg1.Re * arg2.Im;
		Cmplx_multiply(&arg1, &arg2, &result);

		Cmplx_print(&arg1);
		Cmplx_print(&arg2);
		Cmplx_print(&answer);
		Cmplx_print(&result);

		printf("Double multiplication (%lf, %lf) and (%lf, %lf). Expected value (%lf, %lf); Real value (%lf, %lf)\n", arg1.Re, arg1.Im, arg2.Re, arg2.Im, answer.Re, answer.Im, result.Re, result.Im);
		assert(Cmplx_comparison(&result, &answer));

		answer.Re = arg1.Re * digit;
		answer.Im = arg1.Im * digit;
		printf("Double multiplication (%lf, %lf) on digit %lf. ", arg1.Re, arg1.Im, digit);
		Cmplx_multiply_digit(&arg1, digit);
		printf("Expected value (%lf, %lf); Real value (%lf, %lf)\n", answer.Re, answer.Im, arg1.Re, arg1.Im);
		assert(Cmplx_comparison(&arg1, &answer));

		answer.Re = arg2.Re * digit;
		answer.Im = arg2.Im * digit;
		printf("Double multiplication (%lf, %lf) on digit %lf. ", arg2.Re, arg2.Im, digit);
		Cmplx_multiply_digit(&arg2, digit);
		printf("Expected value (%lf, %lf); Real value (%lf, %lf)\n", answer.Re, answer.Im, arg2.Re, arg2.Im);
		assert(Cmplx_comparison(&arg2, &answer));
	}
}

void Mtrx_test() {
	unsigned int order = 3;
	Mtrx_error* code = (Mtrx_error*)malloc(sizeof(Mtrx_error));
	*code = MATRIX_OPERATION_OK;
	Matrix* mtrx1 = Mtrx_create(Get_Cmplx_type_Info(), order, code);
	Matrix* mtrx2 = Mtrx_create(Get_Cmplx_type_Info(), order, code);
	Matrix* mtrx3 = Mtrx_create(Get_Cmplx_type_Info(), order, code);

	for (int i = 0; i < mtrx1->order; i++) {
		for (int j = 0; j < mtrx1->order; j++) {
			mtrx1->type_Info->scan(&mtrx1->elements[i][j]);
			printf("///////\n");
			mtrx2->type_Info->scan(&mtrx2->elements[i][j]);
		}
	}

	Complex** result = (Complex**)malloc(sizeof(Complex*) * mtrx1->order);
	for (int i = 0; i < mtrx1->order; i++) result[i] = (Complex*)malloc(sizeof(Complex) * mtrx1->order);

	Mtrx_add(mtrx1, mtrx2, mtrx3, code);

	for (int i = 0; i < mtrx1->order; i++) {
		for (int j = 0; j < mtrx1->order; j++) {
				mtrx1->type_Info->add(&mtrx1->elements[i][j], &mtrx2->elements[i][j], &result[i][j]);
		}
	}

	for (int i = 0; i < mtrx1->order; i++) {
		for (int j = 0; j < mtrx1->order; j++) {
				assert(mtrx1->type_Info->compairson(&mtrx3->elements[i][j], &result[i][j]));
		}
	}

	if (mtrx1 != NULL) Mtrx_free(mtrx1);
	if (mtrx2 != NULL) Mtrx_free(mtrx2);
	if (mtrx3 != NULL) Mtrx_free(mtrx3);
	free(code);

	for (int i = mtrx1->order - 1; i >= 0; i--) if (result[i] != NULL) free(result[i]);
	if (result != NULL) free(result);

	Free_Cmplx_type_Info();
	Free_Int_type_Info();
}
#endif