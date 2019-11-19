#include "headers/stackListRoutines.h"

/* >includes
<stdio.h>
<stdlib.h>
<string.h>
<malloc.h>
<limits.h>
"data_t.h"
*/

/* >defines
#define STACK_LEN 4000
#define OUT_OF_MEMORY -100
#define STACK_OVERFLOW -101
#define STACK_UNDERFLOW -102
*/

/* >structure
typedef cell data_t;             //значение элемента списка
*/

/* >structure
typedef struct node_tag         //узел списка
{
    data_t *data;               // указатель на значение элемента списка
    struct node_tag *prev;      // предыдущий элемент
} node_t;
*/

/* >structure
typedef struct                  // стек в виде односвязного списка
{
    node_t *head;               // указатель на верхний элемент списка(т.н. "голова")
    int stackLen;               // длина стека
    node_t **freePtr;           // массив свободных адресов
    int freePtrLen;             // длина массива свободных адресов
    size_t dataSize;            // размер одногозначения элемента списка в байтах
} listStack_t;
*/

// >documentation
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
void initList(listStack_t *list) //>signature
{
    list->head = 0;
    list->stackLen = 0;
    list->freePtr = malloc(STACK_LEN * sizeof (void *));
    list->dataSize = sizeof (data_t);
    list->freePtrLen = 0;
}

// >documentation
/*!
 * \brief listPush
 * \param list      // указатель list типа listStack_t, по которому будет происходить доступ к стеку
 * \param ptr       // указатель ptr типа data_t, адрес по которому будет происходить запись значения в верний элемент стека
 * \return          // STACK_OVERFLOW - стек переполнен, EXIT_SUCCESS - успешное исполнени, OUT_OF_MEMORY - нет памяти под стек
 * добавление элемента ptr на верх стека list
 */
int listPush(listStack_t *list, data_t *ptr) //>signature
{
    if(list->stackLen == STACK_LEN)
        return STACK_OVERFLOW;

    node_t *tmp = NULL;

    if(list->freePtrLen == 0)
    {
        tmp = malloc(sizeof (node_t));
        if(!tmp)
            return OUT_OF_MEMORY;

        tmp->data = malloc(list->dataSize);
        if(!tmp->data)
            return OUT_OF_MEMORY;
    }
    else
    {
        tmp = list->freePtr[list->freePtrLen - 1];
        list->freePtr[list->freePtrLen - 1] = 0;
        list->freePtrLen--;
    }

    tmp->prev = list->head;
    list->head = tmp;

    memcpy(tmp->data, ptr, sizeof (data_t));

    list->stackLen++;

    return EXIT_SUCCESS;
}

// >documentation
/*!
 * \brief listPop
 * \param list      // указатель list типа listStack_t, по которому будет происходить доступ к стеку
 * \param ptr       // указатель ptr типа data_t, адрес по которому будет происходить запись значения вернего элемента стека
 * \return          // STACK_UNDERFLOW - стек пуст, EXIT_SUCCESS - успешное исполнение
 * удаление элемента с верха стека list и запись данных элемента в ptr
 */
int listPop(listStack_t *list, data_t *ptr) //>signature
{
    node_t tmp;
    if(list->stackLen == 0)
        return STACK_UNDERFLOW;

    memcpy(ptr, list->head->data, sizeof (data_t));

    tmp.data = list->head->data;
    tmp.prev = list->head->prev;

    list->freePtr[list->freePtrLen] = list->head;
    list->freePtrLen++;

    list->head->data = tmp.data;
    list->head = tmp.prev;

    list->stackLen--;

    return EXIT_SUCCESS;
}

// >documentation
/*!
 * \brief listPeek
 * \param list      // указатель list типа listStack_t, по которому будет происходить доступ к стеку
 * \param data      // указатель data типа data_t, адрес по которому будет происходить запись значения вернего элемента стека
 * \return          // STACK_UNDERFLOW - стек пуст, EXIT_SUCCESS - успешное исполнение
 * просмотр текущего верхнего значения списка
 */
int listPeek(listStack_t *list, data_t *data) //>signature
{
    if(list->stackLen == 0)
        return STACK_UNDERFLOW;

    memcpy(list->head->data, data, sizeof (data_t));

    return EXIT_SUCCESS;
}

// >documentation
/*!
 * \brief freeList
 * \param list      // указатель list типа listStack_t, по которому будет происходить доступ к стеку
 * деконструктор списка
 */
void freeList(listStack_t *list) //>signature
{
    data_t a;
    int tmp = list->stackLen;
    for(int i = 0; i < tmp; i++)
        listPop(list, &a);
    for(int i = 0; i < list->freePtrLen; i++)
    {
        free(list->freePtr[i]->data);
        free(list->freePtr[i]);
    }
    free(list->freePtr);
}

// >documentation
/*!
 * \brief listStatus
 * \param list          // указатель list типа listStack_t, по которому будет происходить доступ к стеку
 * выводит текущий статус стека:
 * указатель на верхний элемент, размер стека
 * массив свободных адресов
 * размер массива свбодных адресов
 */
void listStatus(listStack_t *list) //>signature
{
    printf("\n");
    printf("List status:\n");
    printf("Head = %p\n", (void *)list->head);
    printf("Stack size = %d\n", (unsigned)list->stackLen);
    printf("Free places:");
    for(int i = 0; i < list->freePtrLen; i++)
        printf(" %p", (void *)((list->freePtr[i])));
    printf("\n");
    printf("Length of array of free places = %d\n", list->freePtrLen);
    printf("\n");
}
