#include "headers/header.h"
#include "headers/delete.h"

/*!@brief Функция удаления элемента с головы очереди
 * @brief Реализация:
 * @brief Сдвиг <-- элементов очереди
 * */
/*!
 * @param **head - указатель на структуру очереди, реализованную массивом
 * @param *frnt – позиция первого элемента в очереди
 * @param *rear – позиция последнего элемента в очереди
*/
int arr_delete(arr_queue *head)
{
    int len = head->rear - head->frnt + 1;
    int tmp;

    for (int i = 1; i < len; i++)
        head->qu[i - 1] = head->qu[i];

    head->frnt--;

    return EXIT_SUCCESS;
}

/*!@brief Функция удаления элемента с головы очереди.
 * @brief Реализация:
 * @brief Необходимо удалить первый элемент в очереди, запомнить его указатель, далее сдвинуть все последующие элементы <--
 * */
/*!
 * @param ***head - указатель на структуру очереди, реализованную списком
 * @param *frnt – позиция первого элемента в очереди
 * @param *rear – позиция последнего элемента в очереди
*/
int list_delete(list_queue **head)
{
    list_queue *point = (*head)->p_frnt;
    list_queue *tmp;

    int len = (*head)->rear - (*head)->frnt + 1;

    for (int i = 0; i < len; i++)
    {
        tmp = (*head)->next;
        *head = (*head)->next;
        *head = tmp;
    }

    return EXIT_SUCCESS;
}