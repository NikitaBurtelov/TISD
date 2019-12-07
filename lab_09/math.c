#include "headers/math.h"


int create_1st_matrix(matrix_t *matrix)
{
    if (matrix->columns < matrix->strings)
        while (matrix->columns < matrix->strings)
            delete_string(matrix);
    else
        while (matrix->strings < matrix->columns)
            if (delete_column(matrix))
                return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int create_2nd_matrix(matrix_t *a, matrix_t *b)
{
    matrix_t *pt1 = a, *pt2 = b; // pt1 > pt2
    if (a->strings < b->strings)
    {
        pt1 = b;
        pt2 = a;
    }

    while (pt1->strings > pt2->strings)
        if (add_string(pt2))
            return EXIT_FAILURE;
    while (pt1->columns > pt2->columns)
        if (add_column(pt2))
            return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

matrix_t multipl_matrix(matrix_t *left, matrix_t *right)
{
    matrix_t result;

    if (init_matrix(&result, left->strings, right->columns))
    {
        result.data_pt = NULL;
        return result;
    }

    for (int i = 0; i < result.strings; i++)
        for (int j = 0; j < result.columns; j++)
        {
            result.data_pt[i][j] = 0;
            for (int k = 0; k < right->columns; k++)
                result.data_pt[i][j] += left->data_pt[i][k] * right->data_pt[k][j];
        }

    return result;
}

int create_3rd_matrix(matrix_t *a, matrix_t *b, matrix_t *c, int ro, int gm)
{
    if (ro == 0)
        for (int i = 0; i < a->strings; i++)
            for (int j = 0; j < a->columns; j++)
                a->data_pt[i][j] = (i == j) ? 1 : 0;

    if (gm == 0)
        for (int i = 0; i < b->strings; i++)
            for (int j = 0; j < b->columns; j++)
                b->data_pt[i][j] = (i == j) ? 1 : 0;

    matrix_t tmp;
    if (ro >= 2)
    {
        tmp = multipl_matrix(a, a);
        if (!tmp.data_pt)
            return EXIT_FAILURE;
        *c = tmp;
    }
    else
    {
        init_matrix(c, a->strings, a->columns);
        for (int i = 0; i < a->strings; i++)
            for (int j = 0; j < a->columns; j++)
                c->data_pt[i][j] = a->data_pt[i][j];
    }

    for (int i = 1; i < ro - 1; i++)
    {
        tmp = multipl_matrix(c, a);
        if (!tmp.data_pt)
            return EXIT_FAILURE;
        dest_matrix(c);
        *c = tmp;
    }
    for (int i = 0; i < gm; i++)
    {
        tmp = multipl_matrix(c, b);
        if (!tmp.data_pt)
            return EXIT_FAILURE;
        dest_matrix(c);
        *c = tmp;
    }

    return EXIT_SUCCESS;
}
