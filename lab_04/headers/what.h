#ifndef LAB_04_WHAT_H
#define LAB_04_WHAT_H

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define NMAX 100
#define BUF_LEN 100

//Список int
typedef struct List_tag_int
{
    int value;
    struct List_tag_int *next;
} List_int;

//Список double
typedef struct List_tag_double
{
    double value;
    struct List_tag_double *next;
} List_doubel;

//Массив int
typedef struct
{
    int elem[NMAX];
    int top;
} Mass_int;

//Массив double
typedef struct
{
    double elem[NMAX];
    int top;
} Mass_double;


#endif //LAB_04_WHAT_H
