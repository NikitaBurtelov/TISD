#include "headers/array_routines.h"
#include "headers/my_math.h"
#include "headers/includes.h"

int main(void)
{
    int len = 0;
    int pos = 0;
    double mu1 = 0;
    double mu2 = 0;
    arr_t x = NULL;

    if (scanf("%d", &len) != 1 || len < 1)
        return EXIT_FAILURE;

    if (create_arr((void *)&x, len, sizeof (double)) != EXIT_SUCCESS)
        return EXIT_FAILURE;

    if (arr_in(x, len) != EXIT_SUCCESS)
    {
        delete_arr((void *)&x);
        return EXIT_FAILURE;
    }

    if (mu1_foo(x, len, &mu1) != EXIT_SUCCESS)
    {
        delete_arr((void *)&x);
        return EXIT_FAILURE;
    }

    if (form_a1(&x, &len, mu1) != EXIT_SUCCESS)
    {
        delete_arr((void *)&x);
        return EXIT_FAILURE;
    }

    if (mu2_foo(x, len, &mu2) != EXIT_SUCCESS)
    {
        delete_arr((void *)&x);
        return EXIT_FAILURE;
    }

    if (recreate_arr((void *)&x, len + 3, sizeof (double)) != EXIT_SUCCESS)
    {
        delete_arr((void *)&x);
        return EXIT_FAILURE;
    }

    if (scanf("%d", &pos) != 1 || (pos + 1 > len || pos < 0))
    {
        delete_arr((void *)&x);
        return EXIT_FAILURE;
    }

    insert(x, &len, mu2, pos);
    insert(x, &len, mu2, 0);
    insert(x, &len, mu2, len);

    arr_out(x, len);

    delete_arr((void *)&x);

    return EXIT_SUCCESS;
}
