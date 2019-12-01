#ifndef __MATH_H__
#define __MATH_H__

#include "matrix_routines.h"
#include "includes.h"
#include "types.h"



int create1stMatrix(matrix_t *matrix);

int create2ndMatrix(matrix_t *A, matrix_t *B);

matrix_t multiplMatrix(matrix_t *left, matrix_t *right);

int create3rdMatrix(matrix_t *A, matrix_t *B, matrix_t *C, int ro, int gm);

#endif // __MATH_H__

