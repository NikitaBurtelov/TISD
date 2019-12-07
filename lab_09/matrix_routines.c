#include "headers/matrix_routines.h"


int init_matrix(matrix_t *matrix, int strings, int columns)
{
    matrix->data_pt = malloc(sizeof (long *) * strings);
    if (!matrix->data_pt)
        return EXIT_FAILURE;

    for (int i = 0; i < strings; i++)
    {
        size_t lgsz = sizeof (long int);
        matrix->data_pt[i] = (long *)malloc(lgsz * columns);
        if (!matrix->data_pt)
            return EXIT_FAILURE;
    }

    matrix->columns = columns;
    matrix->strings = strings;

    return EXIT_SUCCESS;
}

int dest_matrix(matrix_t *matrix)
{
    for (int i = 0; i < matrix->strings; i++)
    {
        free(matrix->data_pt[i]);
        matrix->data_pt[i] = NULL;
    }
    free(matrix->data_pt);
    matrix->data_pt = NULL;
    return EXIT_SUCCESS;
}

int matrix_output(matrix_t matrix)
{
    for (int i = 0; i < matrix.strings; i++)
    {
        for (int j = 0; j < matrix.columns; j++)
            printf("%3ld ", matrix.data_pt[i][j]);
        printf("\n");
    }
    return EXIT_SUCCESS;
}

int matrix_input(matrix_t *matrix)
{
    if (scanf("%d", &matrix->strings) != 1 || matrix->strings <= 0)
        return EXIT_FAILURE;
    if (scanf("%d", &matrix->columns) != 1 || matrix->columns <= 0)
        return EXIT_FAILURE;
    init_matrix(matrix, matrix->strings, matrix->columns);
    for (int i = 0; i < matrix->strings; i++)
        for (int j = 0; j < matrix->columns; j++)
            if (scanf("%ld", &(matrix->data_pt[i][j])) != 1)
            {
                dest_matrix(matrix);
                return EXIT_FAILURE;
            }
    return EXIT_SUCCESS;
}

int delete_column(matrix_t *matrix)
{
    long max = matrix->data_pt[0][0];
    int column = 0;
    for (int i = 0; i < matrix->columns; i++)
        for (int j = 0; j < matrix->strings; j++)
            if (max <= matrix->data_pt[j][i])
            {
                max = matrix->data_pt[j][i];
                column = i;
            }

    for (int i = 0; i < matrix->strings; i++)
    {
        for (int j = column; j < matrix->columns - 1; j++)
            matrix->data_pt[i][j] = matrix->data_pt[i][j + 1];
        size_t lgsz = sizeof (long int);
        long *pt = realloc(matrix->data_pt[i], lgsz * (matrix->columns - 1));
        if (!pt)
            return EXIT_FAILURE;
        matrix->data_pt[i] = pt;
    }
    matrix->columns--;

    return EXIT_SUCCESS;
}

int delete_string(matrix_t *matrix)
{
    long max = matrix->data_pt[0][0];
    int string = 0;
    for (int i = 0; i < matrix->columns; i++)
        for (int j = 0; j < matrix->strings; j++)
            if (max <= matrix->data_pt[j][i])
            {
                max = matrix->data_pt[j][i];
                string = j;
            }
    free(matrix->data_pt[string]);
    matrix->data_pt[string] = NULL;
    matrix->strings--;
    for (int i = string; i < matrix->strings; i++)
        matrix->data_pt[i] = matrix->data_pt[i + 1];

    long **pt = realloc(matrix->data_pt, sizeof (long *) * (matrix->strings));
    if (!pt)
        return EXIT_FAILURE;
    else
        matrix->data_pt = pt;

    return EXIT_SUCCESS;
}

int add_column(matrix_t *matrix)
{
    for (int i = 0; i < matrix->strings; i++)
    {
        size_t lgsz = sizeof (long int);
        long *pt = realloc(matrix->data_pt[i], lgsz * (matrix->columns + 1));
        if (!pt)
            return EXIT_FAILURE;
        else
            matrix->data_pt[i] = pt;
        long min = matrix->data_pt[i][0];
        for (int j = 0; j < matrix->columns; j++)
            min = (min < matrix->data_pt[i][j]) ? min : matrix->data_pt[i][j];
        matrix->data_pt[i][matrix->columns] = min;
    }
    matrix->columns++;
    return EXIT_SUCCESS;
}

int add_string(matrix_t *matrix)
{
    long **pt = realloc(matrix->data_pt, sizeof (long *) * (matrix->strings + 1));
    if (!pt)
        return EXIT_FAILURE;
    else
        matrix->data_pt = pt;

    size_t lgsz = sizeof (long int);
    long *pt1 = malloc(lgsz * (matrix->columns));
    if (!pt)
        return EXIT_FAILURE;
    else
        matrix->data_pt[matrix->strings] = pt1;

    for (int i = 0; i < matrix->columns; i++)
    {
        int sum = 0, quant = 0;
        for (int j = 0; j < matrix->strings; j++, quant++)
            sum += matrix->data_pt[j][i];
        if (sum < 0 && (sum % 2))
            sum--;
        matrix->data_pt[matrix->strings][i] = sum / quant;
    }
    matrix->strings++;
    return EXIT_SUCCESS;
}
