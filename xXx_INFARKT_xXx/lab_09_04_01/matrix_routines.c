#include "headers/matrix_routines.h"

/* >includes
"types.h"
"includes.h"
 */

int initMatrix(matrix_t *matrix, int strings, int columns) // >signature
{
    matrix->dataP = malloc(sizeof (long *) * (unsigned)strings);
    if(!matrix->dataP)
        return EXIT_FAILURE;

    for(int i = 0; i < strings; i++)
    {
        matrix->dataP[i] = (long *)malloc(sizeof (long) * (unsigned)columns);
        if(!matrix->dataP)
            return EXIT_FAILURE;
    }

    matrix->columns = columns;
    matrix->strings = strings;

    return EXIT_SUCCESS;
}

int destMatrix(matrix_t *matrix) // >signature
{
    for(int i = 0; i < matrix->strings; i++)
    {
        free(matrix->dataP[i]);
        matrix->dataP[i] = NULL;
    }
    free(matrix->dataP);
    matrix->dataP = NULL;
    return EXIT_SUCCESS;
}

int matrixOutput(matrix_t matrix) // >signature
{
    for(int i = 0; i < matrix.strings; i++)
    {
        for(int j = 0; j < matrix.columns; j++)
            printf("%3ld ", matrix.dataP[i][j]);
        printf("\n");
    }
    return EXIT_SUCCESS;
}

int matrixInput(matrix_t *matrix) // >signature
{
    if(scanf("%d", &matrix->strings) != 1 || matrix->strings <= 0)
        return EXIT_FAILURE;
    if(scanf("%d", &matrix->columns) != 1 || matrix->columns <= 0)
        return EXIT_FAILURE;
    initMatrix(matrix, matrix->strings, matrix->columns);
    for(int i = 0; i < matrix->strings; i++)
        for(int j = 0; j < matrix->columns; j++)
            if(scanf("%ld", &(matrix->dataP[i][j])) != 1)
            {
                destMatrix(matrix);
                return EXIT_FAILURE;
            }
    return EXIT_SUCCESS;
}

int deleteColumn(matrix_t *matrix) // >signature
{
    long max = matrix->dataP[0][0];
    int column = 0;
    for(int i = 0; i < matrix->columns; i++)
        for(int j = 0; j < matrix->strings; j++)
            if(max <= matrix->dataP[j][i])
            {
                max = matrix->dataP[j][i];
                column = i;
            }

    for(int i = 0; i < matrix->strings; i++)
    {
        for(int j = column; j < matrix->columns - 1; j++)
            matrix->dataP[i][j] = matrix->dataP[i][j+1];
        long *pt = realloc(matrix->dataP[i], sizeof(long) * (unsigned)(matrix->columns - 1));
        if(!pt)
            return EXIT_FAILURE;
        matrix->dataP[i] = pt;
    }
    matrix->columns--;

    return EXIT_SUCCESS;
}

int deleteString(matrix_t *matrix) // >signature
{
    long max = matrix->dataP[0][0];
    int string = 0;
    for(int i = 0; i < matrix->columns; i++)
        for(int j = 0; j < matrix->strings; j++)
            if(max <= matrix->dataP[j][i])
            {
                max = matrix->dataP[j][i];
                string = j;
            }
    free(matrix->dataP[string]);
    matrix->dataP[string] = NULL;
    matrix->strings--;
    for(int i = string; i < matrix->strings; i++)
        matrix->dataP[i] = matrix->dataP[i+1];

    long **pt = realloc(matrix->dataP, sizeof (long*) * (unsigned)(matrix->strings));
    if(!pt)
        return EXIT_FAILURE;
    else
        matrix->dataP = pt;

    return EXIT_SUCCESS;
}

int addColumn(matrix_t *matrix) // >signature
{
    for(int i = 0; i < matrix->strings; i++)
    {
        long *pt = realloc(matrix->dataP[i], sizeof (long) * (unsigned)(matrix->columns + 1));
        if(!pt)
            return EXIT_FAILURE;
        else
            matrix->dataP[i] = pt;
        long min = matrix->dataP[i][0];
        for(int j = 0; j < matrix->columns; j++)
            min = (min < matrix->dataP[i][j]) ? min : matrix->dataP[i][j];
        matrix->dataP[i][matrix->columns] = min;
    }
    matrix->columns++;
    return EXIT_SUCCESS;
}

int addString(matrix_t *matrix) // >signature
{
    long **pt = realloc(matrix->dataP, sizeof (long *) *(unsigned)(matrix->strings + 1));
    if(!pt)
        return EXIT_FAILURE;
    else
        matrix->dataP = pt;

    long *pt1 = malloc(sizeof (long) *(unsigned)(matrix->columns));
    if(!pt)
        return EXIT_FAILURE;
    else
        matrix->dataP[matrix->strings] = pt1;

    for(int i = 0; i < matrix->columns; i++)
    {
        int sum = 0, quant = 0;
        for(int j = 0; j < matrix->strings; j++, quant++)
            sum += matrix->dataP[j][i];
        if(sum < 0 && (sum % 2) == -1)
            sum--;
        matrix->dataP[matrix->strings][i] = sum/quant;
    }
    matrix->strings++;
    return EXIT_SUCCESS;
}
