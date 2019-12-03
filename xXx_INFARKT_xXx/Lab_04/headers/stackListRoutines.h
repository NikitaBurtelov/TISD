/*
This header file was generated automaticaly!
Generated at: 03 December 2019 (03.12.2019) At: 14:51:28
Amount of functions        : 6
Amount of documentated     : 6
All functions documentated : True
Amount of structures       : 3
Amount of enums            : 0
Function's names: 
   1 > freeList
   2 > initList
   3 > listPeek
   4 > listPop
   5 > listPush
   6 > listStatus

*/

#ifndef __STACKLISTROUTINES_H__
#define __STACKLISTROUTINES_H__

#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>
#include <stdio.h>
#include "data_t.h"

#define STACK_LEN 4000
#define OUT_OF_MEMORY -100
#define STACK_OVERFLOW -101
#define STACK_UNDERFLOW -102


typedef cell data_t;             //значение элемента списка

typedef struct node_tag         //узел списка
{
    data_t *data;               // указатель на значение элемента списка
    struct node_tag *prev;      // предыдущий элемент
} node_t;

typedef struct                  // стек в виде односвязного списка
{
    node_t *head;               // указатель на верхний элемент списка(т.н. "голова")
    int stackLen;               // длина стека
    node_t **freePtr;           // массив свободных адресов
    int freePtrLen;             // длина массива свободных адресов
    size_t dataSize;            // размер одногозначения элемента списка в байтах
} listStack_t;

/*
* в данной реализации стека как односвязного списка всегда создается указатель на элемент данных для каждого узла
* таким образом изменение следующего синонима позволяет оперировать стеком вне зависимости от типа данных
*
* по умолчанию:
*      typedef int data_t;
*
* для того, чтобы элементом данных стека была следующая структура
*     typedef struct
*     {
*         int a;
*         int b;
*         int c;
*     } exmpl;
* следует заменить int на expmpl
*
* после замены:
*      typedef exmpl data_t;
*/

// >documentation
/*!
* \brief initList
* \param list      // указатель list типа listStack_t, по которому будет происходить доступ к стеку
* конструктор списка
*/
void initList(listStack_t *list);

/*!
* \brief listPush
* \param list      // указатель list типа listStack_t, по которому будет происходить доступ к стеку
* \param ptr       // указатель ptr типа data_t, адрес по которому будет происходить запись значения в верний элемент стека
* \return          // STACK_OVERFLOW - стек переполнен, EXIT_SUCCESS - успешное исполнени, OUT_OF_MEMORY - нет памяти под стек
* добавление элемента ptr на верх стека list
*/
int listPush(listStack_t *list, data_t *ptr);

/*!
* \brief listPop
* \param list      // указатель list типа listStack_t, по которому будет происходить доступ к стеку
* \param ptr       // указатель ptr типа data_t, адрес по которому будет происходить запись значения вернего элемента стека
* \return          // STACK_UNDERFLOW - стек пуст, EXIT_SUCCESS - успешное исполнение
* удаление элемента с верха стека list и запись данных элемента в ptr
*/
int listPop(listStack_t *list, data_t *ptr);

/*!
* \brief listPeek
* \param list      // указатель list типа listStack_t, по которому будет происходить доступ к стеку
* \param data      // указатель data типа data_t, адрес по которому будет происходить запись значения вернего элемента стека
* \return          // STACK_UNDERFLOW - стек пуст, EXIT_SUCCESS - успешное исполнение
* просмотр текущего верхнего значения списка
*/
int listPeek(listStack_t *list, data_t *data);

/*!
* \brief freeList
* \param list      // указатель list типа listStack_t, по которому будет происходить доступ к стеку
* деконструктор списка
*/
void freeList(listStack_t *list);

/*!
* \brief listStatus
* \param list          // указатель list типа listStack_t, по которому будет происходить доступ к стеку
* выводит текущий статус стека:
* указатель на верхний элемент, размер стека
* массив свободных адресов
* размер массива свбодных адресов
*/
void listStatus(listStack_t *list);

#endif // __STACKLISTROUTINES_H__

