#include "headers/includes.h"
#include "headers/types.h"
#include "headers/matrix_routines.h"
#include "headers/math.h"


int main()
{
    matrix_t a, b, c;
    int ro, gm;

    if (matrix_input(&a))
        return EXIT_FAILURE;

    if (matrix_input(&b))
    {
        dest_matrix(&a);
        return EXIT_FAILURE;
    }

    if (scanf("%d", &ro) != 1 || ro < 0)
    {
        dest_matrix(&a);
        dest_matrix(&b);
        return EXIT_FAILURE;
    }

    if (scanf("%d", &gm) != 1 || gm < 0)
    {
        dest_matrix(&a);
        dest_matrix(&b);
        return EXIT_FAILURE;
    }

    create_1st_matrix(&a);
    create_1st_matrix(&b);

    create_2nd_matrix(&a, &b);

    create_3rd_matrix(&a, &b, &c, ro, gm);

    matrix_output(c);

    dest_matrix(&c);
    dest_matrix(&a);
    dest_matrix(&b);
    return EXIT_SUCCESS;
}
