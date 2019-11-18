#include "headers/header.h"
#include "headers/delete.h"

/*!@brief Функция удаления элемента с головы очереди*/
/*!
 * @param **head - указатель на структуру очереди, реализованную массивом
 * @param *frnt – позиция первого элемента в очереди
 * @param *rear – позиция последнего элемента в очереди
*/
int arr_delete(arr_queue *head)
{
    head->frnt--;

    return EXIT_SUCCESS;
}

/*!@brief Функция удаления элемента с головы очереди*/
/*!
 * @param ***head - указатель на структуру очереди, реализованную списком
 * @param *frnt – позиция первого элемента в очереди
 * @param *rear – позиция последнего элемента в очереди
*/
int list_delete(list_queue **head)
{
    list_queue *point = NULL;

    if ((*head) == NULL)
        return EXIT_FAILURE;

    point = *head;
    *head = (*head)->next;

    free(point);

    return EXIT_SUCCESS;
}