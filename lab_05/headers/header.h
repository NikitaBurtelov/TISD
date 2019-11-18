#ifndef LAB_05_HEADER_H
#define LAB_05_HEADER_H

#define QMAX 100

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

//Массив int
/*!
 * @param *frnt – позиция первого элемента в очереди
 * @param *rear – позиция последнего элемента в очереди
*/
typedef struct arr_queue_struct
{
    int qu[QMAX];
    int rear, frnt;
} arr_queue;

//Список int
typedef struct List_queue_struct
{
    int value;
    int rear, frnt;
    struct List_queue_struct *next;
    struct List_queue_struct *p_frnt;
} list_queue;

int init_arr_queue(arr_queue *head);

int init_list_queue(list_queue **head);

#endif //LAB_05_HEADER_H
