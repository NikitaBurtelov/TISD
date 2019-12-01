#include "headers/array_routines.h"
#include "headers/includes.h"
#include "headers/my_math.h"
#include <time.h>


int main()
{
    int len = 6, len2 = 9, len3 = 12;
    int pos = 2, pos2 = 3, pos3 = 7;
    double mu1 = 0, mu12 = 0, mu13 = 0;
    double mu2 = 0, mu22 = 0, mu23 = 0;
    arr_t x = NULL, x2 = NULL, x3 = NULL;

    create_arr((void *)&x, len, sizeof (double));
    create_arr((void *)&x2, len2, sizeof (double));
    create_arr((void *)&x3, len3, sizeof (double));

    srand(time(NULL));

    for (int i = 0; i < len; i++)
        x[i] = rand() % 10 + i;

    for (int i = 0; i < len2; i++)
        x2[i] = rand() % 10 + i;

    for (int i = 0; i < len3; i++)
        x3[i] = rand() % 10 + i;

    my_sort(x, len);
    my_sort(x2, len2);
    my_sort(x3, len3);

    mu1_foo(x, len, &mu1);
    mu1_foo(x2, len2, &mu12);
    mu1_foo(x3, len3, &mu13);

    form_a1(&x, &len, mu1);
    form_a1(&x2, &len2, mu12);
    form_a1(&x3, &len3, mu13);

    mu2_foo(x, len, &mu2);
    mu2_foo(x2, len2, &mu22);
    mu2_foo(x3, len3, &mu23);

    recreate_arr((void *)&x, len + 3, sizeof (double));
    recreate_arr((void *)&x2, len2 + 3, sizeof (double));
    recreate_arr((void *)&x3, len3 + 3, sizeof (double));

    insert(x, &len, mu2, pos);
    insert(x, &len, mu2, 0);
    insert(x, &len, mu2, len);

    insert(x2, &len2, mu22, pos2);
    insert(x2, &len2, mu22, 0);
    insert(x2, &len2, mu22, len);

    insert(x3, &len3, mu23, pos3);
    insert(x3, &len3, mu23, 0);
    insert(x3, &len3, mu23, len);

    arr_out(x, len);
    arr_out(x2, len2);
    arr_out(x3, len3);

    delete_arr((void *)&x);
    delete_arr((void *)&x2);
    delete_arr((void *)&x3);

    return EXIT_SUCCESS;
    return EXIT_FAILURE;
}
