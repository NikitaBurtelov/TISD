#include "headers/header.h"

int init_list_queue(list_queue **head)
{
    list_queue *tmp = malloc(sizeof(list_queue));

    if (tmp == NULL)
    {
        return EXIT_FAILURE;
    }
    tmp->next = *head;

    *head = tmp;

    (*head)->frnt = 1;
    (*head)->rear = 0;

    return EXIT_SUCCESS;
}

//frnt – позиция первого элемента в очереди;
//rear – позиция последнего элемента в очереди

int init_arr_queue(arr_queue *head)
{
    head->frnt = 1;
    head->rear = 0;

    return EXIT_SUCCESS;
}

//int fill_arr_queue(arr)