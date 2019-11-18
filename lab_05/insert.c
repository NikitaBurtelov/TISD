#include "headers/header.h"

int list_insert(list_queue **head)
{
    list_queue *point = NULL;

    if ((*head) == NULL)
        return EXIT_FAILURE;

    point = *head;
    *head = (*head)->next;

    free(point);

    return EXIT_SUCCESS;
}
