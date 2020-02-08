#ifndef ROUTINES_H
#define ROUTINES_H

#include "types.h"

/*!
 * \brief freeArr // удаляет вектор целых чисел
 * \param arr // указатель на вектор
 * \return // возвращает NULL
 */
void* freeArr(intArr_t *arr)
{
    free(arr->data);
    free(arr);
    return NULL;
}

/*!
 * \brief simpleMultiples // разложение числа num в вектор arr простых чисел
 * \param num // число, которое будет разложено в вектор простых чисел
 * \return arr // указатель на вектор простых чисел
 */
intArr_t *simpleMultiples(int num)
{
    if (num < 2)
        return NULL;

    int tmp[2000];
    intArr_t *arr = NULL;

    int t = num, i = 2, j = 0;
    while(i <= t)
    {
        if(t % i == 0)
        {
            tmp[j] = i;
            t = t / i;
            j++;
        }
        else
            i = i + 1;
    }

    arr = malloc(sizeof (intArr_t));
    if(!arr)
        exit(1);
    arr->len = j;
    arr->data = malloc(sizeof (int) * (unsigned)j);
    for(int i = 0; i < arr->len; i++)
        arr->data[i] = tmp[i];

    if(!arr->data)
    {
        free(arr);
        exit(1);
    }

    return arr;
}

/*!
 * \brief append // добавление узла в конец списка
 * \param list // указатель на список
 * \param num // значение узла
 * \return // указатель на добавленный узел при успехе, NULL при ошибке
 */
void *append(list_t *list, data_t num)
{
    if(!list->head)
    {
        list->head = malloc(sizeof (node_t));
        if(!list->head)
            return NULL;

        list->head->data = malloc(sizeof (data_t));
        if(!list->head->data)
        {
            free(list->head);
            return NULL;
        }

        list->tail = list->head;
        *list->head->data = num;
        list->head->prev = NULL;
        list->listLen++;

        return list->head;
    }

    else
    {
        node_t *tmp = malloc(sizeof (node_t));
        if(!tmp)
            return NULL;

        tmp->data = malloc(sizeof (data_t));
        if(!tmp->data)
        {
            free(tmp);
            return NULL;
        }

        *tmp->data = num;
        tmp->prev = list->tail;
        list->tail = tmp;
        list->listLen++;

        return list->tail;
    }

}

/*!
 * \brief delete // удаляем последний узел из списка и возвращает указетель назначение удаленного узла
 * \param list // указатель на список
 * \return data // указатель на значение удаленного узла списка
 */
data_t *delete(list_t *list)
{
    data_t *data;
    if(!list->head)
        return NULL;
    else if (list->listLen == 1)
    {
        data = list->head->data;
        free(list->head);
        list->head = list->tail = NULL;
    }
    else
    {
        data = list->tail->data;
        node_t *tmp = list->tail->prev;
        free(list->tail);
        list->tail = tmp;
    }
    return data;
}

/*!
 * \brief freeList // удаляет список
 * \param list // указатель на список
 */
void freeList (list_t *list)
{
    while(list->tail)
    {
        free(delete(list));
    }
}

/*!
 * \brief printList // печататет содержимое списка согласно тз
 * \param list // указатель на список
 */
void printList(list_t *list)
{
    node_t *tmp = list->tail;

    for(int i = 0; i < list->listLen; i++)
    {
        printf("%d %d ", tmp->data->num, tmp->data->pow);
        tmp = tmp->prev;
    }
    printf("1\n");
}

/*!
 * \brief numToList // переводит вектор простых чисел в список простых чисел
 * \param list // указатель на список
 * \param num // число
 */
list_t *numToList (list_t *list, int num)
{
    intArr_t *arr = simpleMultiples(num);
    if(!arr)
        return NULL;
    for(int j = 0; j < arr->len;)
    {
        data_t tmp = {arr->data[j], 1};
        j++;

        for(; arr->len > j && tmp.num == arr->data[j]; j++)
            tmp.pow++;

        append(list, tmp);
    }
    freeArr(arr);

    return list;
}

#endif // ROUTINES_H
