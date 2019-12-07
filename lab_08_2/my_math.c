#include "headers/my_math.h"

void my_sort(arr_t arr, int len)
{
    int k = 0;
    for (double *i = arr; i < arr + len - 1; i++, k++)
        for (double *j = arr; j < arr + len - k - 1; j++)
            if (*j > *(j + 1))
            {
                double tmp = *j;
                *j = *(j + 1);
                *(j + 1) = tmp;
            }
}

int mu1_foo(arr_t p, int len, double *mu1)
{
    double nmr_sum = 0, dnmr_sum = 0;
    arr_t x = NULL;

    if (create_arr((void *)&x, len, sizeof (double)) != EXIT_SUCCESS)
        return EXIT_FAILURE;

    // Подсчет слагаемых, находящихся в знаменателе САВ
    for (int i = 0; i < len; i++)
    {
        *(x + i) = *(p + i) * (i + 1) * (i + 1);
        dnmr_sum += (i + 1) * (i + 1);
    }

    my_sort(x, len);

    // Вычисление значения μ1
    for (double *i = x; i < x + len; i++)
        nmr_sum += *i;

    *mu1 = nmr_sum / dnmr_sum;

    delete_arr((void *)&x);

    return EXIT_SUCCESS;
}

int mu2_foo(arr_t p, int len, double *mu2)
{
    arr_t x = NULL;

    if (create_arr((void *)&x, len, sizeof (double)) != EXIT_SUCCESS)
        return EXIT_FAILURE;

    // Вычисление элементов последовательности для подсчета μ2
    for (double *i = p, *j = x; i < p + len; i++, j++)
        *j = *i / len;

    my_sort(x, len);

    // Вычисление μ2
    for (double *i = x; i < x + len; i++)
        *mu2 += *i;

    delete_arr((void *)&x);

    return EXIT_SUCCESS;
}

int form_a1(arr_t *p, int *len, double mu1)
{
    mu1 = fabs(mu1);

    for (double *i = *p; i < *p + *len;)
        if (fabs(*i) - mu1 > EPS)
        {
            for (double *j = i; j < *p + *len - 1; j++)
            {
                *j = *(j + 1);
            }
            (*len)--;
        }
        else
            i++;

    if (recreate_arr((void *)p, *len, sizeof (double)) != EXIT_SUCCESS || (*len == 0))
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

