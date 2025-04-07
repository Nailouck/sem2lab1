#include "interface.h"

#define ADD 0
#define MULTIPLY 1
#define MULTIPLY_ON_DIGIT 2

unsigned short int type_choice() {
	unsigned short int choice;
	do {
		printf("What type of matrix do you prefer\n 0 - int\n 1 - complex\n");
		scanf("%hd", &choice); 
	} while (choice != 1 && choice != 0);
	return choice;
}

unsigned short int operation_choice() {
	unsigned short int choice;
	do {
		printf("What operation do you prefer\n0 - Addition\n1 - Multiplication\n2 - Multiplication on digit\n");
		scanf("%hd", &choice);
	} while (choice != 2 && choice != 1 && choice != 0);
	return choice;
}

unsigned short int get_matrix_order() {
    unsigned short int order;
    printf("What order of matrix do you want?\n");
    scanf("%hd", &order);
    return order;
}

 void get_conditions(int argc, char* argv[], unsigned short int* choiced_operation, unsigned short int* choiced_type) {

    *choiced_operation = 0;
    *choiced_type = 0;

 	int flag;
 	bool operation_flag = false;
 	bool type_flag = false;

 	while (flag = getopt(argc, argv, "o:t:") != -1) {
 		switch (flag) {

 		case 'o':

 			operation_flag = true;

 			if (strcmp(optarg, "0") != 0 && strcmp(optarg, "1") != 0 && strcmp(optarg, "2") != 0) {
 				printf("Operation has been writen wrong.\n");
 				*choiced_operation = operation_choice();
 			}

 			else {
 				*choiced_operation = atoi(optarg);
 			}
 			break;

 		case 't':

 			type_flag = true;

 			if (strcmp(optarg, "0") != 0 && strcmp(optarg, "1") != 0) {
 				printf("Type of matrix has been writen wrong.\n");
 				*choiced_type = type_choice();
 			}

 			else {
 				*choiced_type = atoi(optarg);
 			}
 			break;

 		}
 	}

 	if (operation_flag == false) *choiced_operation = operation_choice();
 	if (type_flag == false) *choiced_type = type_choice();

    return;
 }

 double get_digit() {
     double digit;
     printf("Multiply on what digit do you want?\n");
     scanf("%lf", &digit);
     return digit;
 }

 void operation(unsigned short int choiced_operation, unsigned short int choiced_type, Mtrx_error* code) {

    #define GET_TYPE_INFO (choiced_type == 0 ? Get_Int_type_Info() : Get_Cmplx_type_Info())
    
    Matrix* mtrx = Mtrx_create(GET_TYPE_INFO, get_matrix_order(), code);

    if (*code != MATRIX_OPERATION_OK) {
        Mtrx_free(mtrx);
        return;
     }
     *code = MATRIX_OPERATION_FAILED;

     Mtrx_fill(mtrx, code);

     if (*code != MATRIX_OPERATION_OK) {
        Mtrx_free(mtrx);
        return;
     }
     *code = MATRIX_OPERATION_FAILED;

     switch (choiced_operation) {

     case ADD: {

         Matrix* mtrx1 = Mtrx_create(GET_TYPE_INFO, get_matrix_order(), code);

         if (*code != MATRIX_OPERATION_OK) {
            Mtrx_free(mtrx);
            Mtrx_free(mtrx1);
            return;
         }
        *code = MATRIX_OPERATION_FAILED;

         Mtrx_fill(mtrx1, code);

         if (*code != MATRIX_OPERATION_OK) {
            Mtrx_free(mtrx);
            Mtrx_free(mtrx1);
            return;
         }
        *code = MATRIX_OPERATION_FAILED;

         Matrix* result_mtrx = Mtrx_create(GET_TYPE_INFO, mtrx->order, code);

         if (*code != MATRIX_OPERATION_OK) {
            Mtrx_free(mtrx);
            Mtrx_free(mtrx1);
            Mtrx_free(result_mtrx);
            return;
         }
        *code = MATRIX_OPERATION_FAILED;

         Mtrx_add(mtrx, mtrx1, result_mtrx, code);

         if (*code != MATRIX_OPERATION_OK) {
            Mtrx_free(mtrx);
            Mtrx_free(mtrx1);
            Mtrx_free(result_mtrx);
            return;
         }
        *code = MATRIX_OPERATION_FAILED;

         Mtrx_print(result_mtrx, code);

         if (*code != MATRIX_OPERATION_OK) {
            Mtrx_free(mtrx);
            Mtrx_free(mtrx1);
            Mtrx_free(result_mtrx);
            return;
         }
        *code = MATRIX_OPERATION_FAILED;

         Mtrx_free(mtrx);
         Mtrx_free(mtrx1);
         Mtrx_free(result_mtrx);
         break;
     }

     case MULTIPLY: {

         Matrix* mtrx1 = Mtrx_create(GET_TYPE_INFO, get_matrix_order(), code);

         if (*code != MATRIX_OPERATION_OK) {
            Mtrx_free(mtrx);
            Mtrx_free(mtrx1);
            return;
         }
         *code = MATRIX_OPERATION_FAILED;

         Mtrx_fill(mtrx1, code);

         if (*code != MATRIX_OPERATION_OK) {
            Mtrx_free(mtrx);
            Mtrx_free(mtrx1);
            return;
         }
         *code = MATRIX_OPERATION_FAILED;

         Matrix* result_mtrx = Mtrx_create(GET_TYPE_INFO, mtrx->order, code);

         if (*code != MATRIX_OPERATION_OK) {
            Mtrx_free(mtrx);
            Mtrx_free(mtrx1);
            Mtrx_free(result_mtrx);
            return;
         }
         *code = MATRIX_OPERATION_FAILED;

         Mtrx_multiply(mtrx, mtrx1, result_mtrx, code);

         if (*code != MATRIX_OPERATION_OK) {
            Mtrx_free(mtrx);
            Mtrx_free(mtrx1);
            Mtrx_free(result_mtrx);
            return;
         }
         *code = MATRIX_OPERATION_FAILED;

         Mtrx_print(result_mtrx, code);

         if (*code != MATRIX_OPERATION_OK) {
            Mtrx_free(mtrx);
            Mtrx_free(mtrx1);
            Mtrx_free(result_mtrx);
            return;
         }
         *code = MATRIX_OPERATION_FAILED;

         Mtrx_free(mtrx);
         Mtrx_free(mtrx1);
         Mtrx_free(result_mtrx);
         break;
     }

     case MULTIPLY_ON_DIGIT: {

         Mtrx_multiply_digit(mtrx, get_digit(), code);

         if (*code != MATRIX_OPERATION_OK) {
            Mtrx_free(mtrx);
            return;
         }
         *code = MATRIX_OPERATION_FAILED;

         Mtrx_print(mtrx, code);

         if (*code != MATRIX_OPERATION_OK) {
            Mtrx_free(mtrx);
            return;
         }
         *code = MATRIX_OPERATION_FAILED;

         Mtrx_free(mtrx);
         break;
     }

     }
 }

 void run(int argc, char* argv[], Mtrx_error* code) {
    while (true) {
     char choice;
     do {
         printf("Do you want to continue? Y/N\n");
         scanf(" %c", &choice);
     } while (choice != 'Y' && choice != 'N' && choice != 'y' && choice != 'n');

     if (choice == 'N' || choice == 'n') {
        *code = MATRIX_OPERATION_OK;
        return;
    }

     unsigned short int choiced_operation;
     unsigned short int choiced_type;

     get_conditions(argc, argv, &choiced_operation, &choiced_type);
     operation(choiced_operation, choiced_type, code);
 }

}
