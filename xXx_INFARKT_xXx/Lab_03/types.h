#ifndef TYPES_H
#define TYPES_H

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

#endif // TYPES_H
