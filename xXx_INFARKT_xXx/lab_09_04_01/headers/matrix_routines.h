#ifndef __MATRIX_ROUTINES_H__
#define __MATRIX_ROUTINES_H__

#include "includes.h"
#include "types.h"



int initMatrix(matrix_t *matrix, int strings, int columns);

int destMatrix(matrix_t *matrix);

int matrixOutput(matrix_t matrix);

int matrixInput(matrix_t *matrix);

int deleteColumn(matrix_t *matrix);

int deleteString(matrix_t *matrix);

int addColumn(matrix_t *matrix);

int addString(matrix_t *matrix);

#endif // __MATRIX_ROUTINES_H__