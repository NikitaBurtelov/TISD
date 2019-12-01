#include "headers/math.h"

/* >includes
"includes.h"
"types.h"
"matrix_routines.h"
*/


int create1stMatrix(matrix_t *matrix) // >signature
{
    if(matrix->columns < matrix->strings)
        while(matrix->columns < matrix->strings)
            deleteString(matrix);
    else
        while(matrix->strings < matrix->columns)
            if(deleteColumn(matrix))
                return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int create2ndMatrix(matrix_t *A, matrix_t *B) // >signature
{
    matrix_t *pt1 = A, *pt2 = B; // pt1 > pt2
    if(A->strings < B->strings)
    {
        pt1 = B;
        pt2 = A;
    }

    while (pt1->strings > pt2->strings)
        if(addString(pt2))
            return EXIT_FAILURE;
    while (pt1->columns > pt2->columns)
        if(addColumn(pt2))
            return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

matrix_t multiplMatrix(matrix_t *left, matrix_t *right) // >signature
{
    matrix_t result;

    if(initMatrix(&result, left->strings, right->columns))
    {
        result.dataP = NULL;
        return result;
    }

    for(int i = 0; i < result.strings; i++)
        for(int j = 0; j < result.columns; j++)
        {
            result.dataP[i][j] = 0;
            for(int k = 0; k < right->columns; k++)
                result.dataP[i][j] += left->dataP[i][k] * right->dataP[k][j];
        }

    return result;
}

int create3rdMatrix(matrix_t *A, matrix_t *B, matrix_t *C, int ro, int gm) //>signature
{
    if(ro == 0)
        for(int i = 0; i < A->strings; i++)
            for(int j = 0; j < A->columns; j++)
                A->dataP[i][j] = (i == j) ? 1 : 0;

    if(gm == 0)
        for(int i = 0; i < B->strings; i++)
            for(int j = 0; j < B->columns; j++)
                B->dataP[i][j] = (i == j) ? 1 : 0;

    matrix_t tmp;
    if(ro >= 2)
    {
        tmp = multiplMatrix(A, A);
        if(!tmp.dataP)
            return EXIT_FAILURE;
        *C = tmp;
    }
    else
    {
        initMatrix(C, A->strings, A->columns);
        for(int i = 0; i < A->strings; i++)
            for(int j = 0; j < A->columns; j++)
                C->dataP[i][j] = A->dataP[i][j];
    }

    for(int i = 1; i < ro - 1; i++)
    {
        tmp = multiplMatrix(C, A);
        if(!tmp.dataP)
            return EXIT_FAILURE;
        destMatrix(C);
        *C = tmp;
    }
    for(int i = 0; i < gm; i++)
    {
        tmp = multiplMatrix(C, B);
        if(!tmp.dataP)
            return EXIT_FAILURE;
        destMatrix(C);
        *C = tmp;
    }

    return EXIT_SUCCESS;
}
