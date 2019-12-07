#include "headers/array_routines.h"

int create_arr(void **p, int len, size_t size_of_type)
{
    *p = malloc(len * size_of_type);

    if (!*p)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int recreate_arr(void **p, int new_len, size_t size_of_type)
{
    if (*p)
    {
        void *new_p = realloc(*p, size_of_type * new_len);
        if (new_p)
            *p = new_p;
        else
            return EXIT_FAILURE;
    }
    else
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int delete_arr(void **p)
{
    if (*p)
    {
        free(*p);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int arr_in(arr_t p, int len)
{
    double *i = p;
    for (; i < p + len; i++)
        if (scanf("%lf", i) != 1)
            return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

void insert(arr_t p, int *len, double elem, int pos)
{
    for (double *i = p + *len; i > p + pos; i--)
        *i = *(i - 1);
    *(p + pos) = elem;
    *len += 1;
}

void arr_out(arr_t p, int len)
{
    for (double *i = p; i < p + len; i++)
        printf("%lf ", *i);
    printf("\n");
}
