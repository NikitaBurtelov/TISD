#ifndef TYPESROUTINES_H
#define TYPESROUTINES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>

// узел
typedef struct node_t
{
    struct node_t *prev;
    struct node_t *next;
    int index;
    int data;
} node_t;

// Двусвязный список
typedef struct list_t
{
    node_t *head;
    node_t *tail;
    node_t *currentPt;
    int curren_num;
    int len;
}list_t;

// динамическая матрица целых чисел
typedef struct
{
    int **data;            // указатель на первую строку матрицы
    unsigned columns;      // количество столбцов
    unsigned strings;      // количество строк
} intMatrix_t;

// динамический массив целых чисел
typedef struct
{
    unsigned size;  // размер массива
    int *data;      // указатель на первый элемент массива
} intVector_t;

// представление разряженной матрицы
typedef struct
{
    intVector_t A;           // вектор A содержит значения ненулевых элементов;
    intVector_t JA;          // вектор JA содержит номера столбцов для элементов вектора A;
    list_t IA;               // связный список IA, в элементе Nk которого находится номер компонент в A и JA, с которых начинается описание строки Nk матрицы A.
} sparceMatrix_t;


/*               КОНСТРУКТОРЫ И ДЕСТРУКТОРЫ                    */
int initVector(int **p, unsigned len)
{
    *p = calloc(len, sizeof (int));

    if (!*p)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int destVector(int **p)
{
    if (*p)
    {
        free(*p);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int initMatrix(int ***p, unsigned strings, unsigned columns)
{
    *p = malloc(strings * sizeof (int *));

    if (!*p)
        return EXIT_FAILURE;

    for(unsigned i = 0; i < strings; i++)
        initVector(&((*p)[i]), (unsigned)columns);
    return EXIT_SUCCESS;
}

int destMatrix(int ***p, unsigned strings)
{
    for(unsigned i = 0; i < strings; i++)
        free((*p)[i]);
    free(*p);
    return EXIT_SUCCESS;
}


/*               ВВОД И ВЫВОД НЕУПАКОВАННОЙ МАТРИЦЫ                       */
int intMatrixInput(intMatrix_t *p)
{
    if(scanf("%d %d", &p->strings, &p->columns) != 2)
        exit(1);

    initMatrix(&p->data, p->strings, p->columns);

    for(unsigned i = 0; i < p->strings; i++)
        for(unsigned j = 0; j < p->columns; j++)
            if(scanf("%d", &p->data[i][j]) != 1)
                exit(1);

    return EXIT_SUCCESS;
}

void intMatrixOutput(intMatrix_t *p)
{
    for(unsigned i = 0; i < p->strings; i++)
    {
        for(unsigned j = 0; j < p->columns; j++)
            printf("%d ", p->data[i][j]);
        printf("\n");
    }
}

#endif // TYPESROUTINES_H
