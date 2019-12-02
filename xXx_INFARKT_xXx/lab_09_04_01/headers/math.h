#ifndef MATH_H
#define MATH_H

#include "matrix_routines.h"
#include "includes.h"
#include "types.h"


int create_1st_matrix(matrix_t *matrix);

int create_2nd_matrix(matrix_t *a, matrix_t *b);

matrix_t multipl_matrix(matrix_t *left, matrix_t *right);

int create_3rd_matrix(matrix_t *a, matrix_t *b, matrix_t *c, int ro, int gm);

#endif

