#include "headers/output.h"

void print_struct_mass(Mass_double p, Mass_int s, int type_mass)
{
    if (type_mass == 0)
        for (int i = 0; i <= p.top; i++)
            printf("\n%d: %lf",i, p.elem[i]);
    else
    {
        for (int i = 0; i <= s.top; i++)
            printf("\n%d: %d",i, s.elem[i]);
    }
}

void print_struct_list_int(const List_int *head)
{
    int count = 0;
    while(head)
    {
        printf("\n%p: %d\n",head->next, head->value);
        head = head->next;
        count++;
    }
}