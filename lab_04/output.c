#include "headers/output.h"

void print_struct_mass(Mass_double p, Mass_int s, int type_mass)
{
    printf("GOPA");
    if (type_mass == 0)
        for (int i = 0; i <= p.top; i++)
            printf("\n%d: %lf",i, p.elem[i]);
    else
    {
        for (int i = 0; i <= s.top; i++)
            printf("\n%d: %d",i, s.elem[i]);
    }
}