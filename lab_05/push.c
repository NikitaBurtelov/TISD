#include "headers/header.h"
#include "headers/push.h"

int push_li(list_queue **head)
{
    list_queue *tmp = malloc(sizeof(list_queue));
    list_queue *buf_point = (*head)->p_frnt;

    int buf_rear = (*head)->rear, buf_frnt = (*head)->frnt;

    if (tmp == NULL)
    {
        return EXIT_FAILURE;
    }
    tmp->next = *head;

    *head = tmp;

    (*head)->rear = buf_rear;
    (*head)->frnt = buf_frnt;
    (*head)->p_frnt = buf_point;

    return EXIT_SUCCESS;
}

