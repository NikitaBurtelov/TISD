#include "headers/math.h"
#include "headers/includes.h"
#include "headers/matrix_routines.h"


int main(void)
{
    matrix_t a, b, c;
    matrix_t a1, b1, c1;
    matrix_t a2, b2, c2;
    int ro = 2, gm = 3;
    int ro1 = 1, gm1 = 5;
    int ro2 = 0, gm2 = 1;

    init_matrix(&a, 5, 3);
    init_matrix(&b, 3, 5);

    init_matrix(&a1, 6, 7);
    init_matrix(&b1, 7, 6);

    init_matrix(&a2, 4, 10);
    init_matrix(&b2, 10, 4);

    srand(time(NULL));

    for (int i = 0; i < a.strings; i++)
        for (int j = 0; j < a.columns; j++)
            a.data_pt[i][j] = rand() % 2 + i;

    for (int i = 0; i < b.strings; i++)
        for (int j = 0; j < b.columns; j++)
            b.data_pt[i][j] = rand() % 2 + i;


    for (int i = 0; i < a1.strings; i++)
        for (int j = 0; j < a1.columns; j++)
            a1.data_pt[i][j] = rand() % 2 + i;

    for (int i = 0; i < b1.strings; i++)
        for (int j = 0; j < b1.columns; j++)
            b1.data_pt[i][j] = rand() % 2 + i;


    for (int i = 0; i < a2.strings; i++)
        for (int j = 0; j < a2.columns; j++)
            a2.data_pt[i][j] = rand() % 2 + i;

    for (int i = 0; i < b2.strings; i++)
        for (int j = 0; j < b2.columns; j++)
            b2.data_pt[i][j] = rand() % 2 + i;

    create_1st_matrix(&a);
    create_1st_matrix(&a1);
    create_1st_matrix(&a2);
    create_1st_matrix(&b);
    create_1st_matrix(&b1);
    create_1st_matrix(&b2);

    create_2nd_matrix(&a, &b);
    create_2nd_matrix(&a1, &b1);
    create_2nd_matrix(&a2, &b2);

    create_3rd_matrix(&a, &b, &c, ro, gm);
    create_3rd_matrix(&a1, &b1, &c1, ro1, gm1);
    create_3rd_matrix(&a2, &b2, &c2, ro2, gm2);

    add_column(&a);
    add_column(&a1);
    add_column(&a2);
    delete_column(&a);
    delete_column(&a1);
    delete_column(&a2);
    add_string(&a);
    add_string(&a1);
    add_string(&a2);
    delete_string(&a);
    delete_string(&a1);
    delete_string(&a2);

    add_column(&b);
    add_column(&b1);
    add_column(&b2);
    delete_column(&b);
    delete_column(&b1);
    delete_column(&b2);
    add_string(&b);
    add_string(&b1);
    add_string(&b2);
    delete_string(&b);
    delete_string(&b1);
    delete_string(&b2);

    add_column(&c);
    add_column(&c1);
    add_column(&c2);
    delete_column(&c);
    delete_column(&c1);
    delete_column(&c2);
    add_string(&c);
    add_string(&c1);
    add_string(&c2);
    delete_string(&c);
    delete_string(&c1);
    delete_string(&c2);


    matrix_output(a);
    matrix_output(b);
    matrix_output(c);

    matrix_output(a1);
    matrix_output(b1);
    matrix_output(c1);

    matrix_output(a1);
    matrix_output(b1);
    matrix_output(c1);

    dest_matrix(&a);
    dest_matrix(&a1);
    dest_matrix(&a2);
    dest_matrix(&b);
    dest_matrix(&b1);
    dest_matrix(&b2);
    dest_matrix(&c);
    dest_matrix(&c1);
    dest_matrix(&c2);

    return EXIT_SUCCESS;
}
