#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

#include "matrix.h"
#include "MatrixError.h"
#include "complex.h"
#include "integer.h"
#include "TypeInfo.h"

unsigned short int type_choice();

unsigned short int operation_choice();

unsigned short int get_matrix_order();

void get_conditions(int argc, char* argv[], unsigned short int* choiced_operation, unsigned short int* choiced_type);

double get_digit();

void operation(unsigned short int choiced_operation, unsigned short int choiced_type, Mtrx_error* code);

void run(int argc, char* argv[], Mtrx_error* code);

#endif