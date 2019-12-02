#ifndef MATRIX_ROUTINES_H
#define MATRIX_ROUTINES_H

#include "includes.h"
#include "types.h"


int init_matrix(matrix_t *matrix, int strings, int columns);

int dest_matrix(matrix_t *matrix);

int matrix_output(matrix_t matrix);

int matrix_input(matrix_t *matrix);

int delete_column(matrix_t *matrix);

int delete_string(matrix_t *matrix);

int add_column(matrix_t *matrix);

int add_string(matrix_t *matrix);

#endif

