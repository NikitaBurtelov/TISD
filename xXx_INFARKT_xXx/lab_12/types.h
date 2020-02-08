#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct intArr_t // вектор целых чисел
{
    int *data; // указатель на массив
    int len; // его длина
}intArr_t;

typedef struct data_t // cтруктура данных которая пишется в список
{
    int num; // число
    int pow; // степнь числа num
} data_t;

typedef struct node_t         //узел списка
{
    data_t *data;               // указатель на значение элемента списка
    struct node_t *prev;      // предыдущий элемент
} node_t;

typedef struct list_t                 // стек в виде односвязного списка
{
    node_t *head;               // указатель на верхний элемент списка(т.н. "голова")
    node_t *tail;               // указатель на последний эдемент списка(т.н. "хвост")
    int listLen;               // длина стека
} list_t;

#endif // TYPES_H
