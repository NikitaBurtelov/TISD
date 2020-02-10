#include "headers/stackArrRoutines.h"

/* >includes
<stdio.h>
<stdlib.h>
<string.h>
<malloc.h>
*/

/* >defines
#define STACK_ARR_LEN 100
#define OUT_OF_MEMORY -100
#define STACK_OVERFLOW -101
#define STACK_UNDERFLOW -102
*/

/* >structure
typedef struct          // реализация стека как динамического массива
{
    void *bot;      //указатель на начало стека      ↓                                                      (указывает на первый байт первого значения)
    //                                              [filled][filled]...[filled][not_filled]...[not_filled]

    void *top;      //ending pointer of stack                                                  ↓            (указывает на первый байт последнего значения)
    //                                              [filled][filled]...[filled][not_filled]...[not_filled]

    void *curr;     //current pointer of stack                                  ↓                           (указывает на первый байт первого не действительного значения)
    //                                              [filled][filled]...[filled][not_filled]...[not_filled]

    size_t sizeOfField;   //размер одного значения в байтах

    int stackLen;

} arrStack_t;
*/

// >documentation
/*!
 * \brief initArr
 * \param ptr           // указатель ptr на переменную типа arrStack_t, адрес по которому можно будет получить доступ к стеку
 * \param size_of_type  // размер size_of_type 1 значения типа size_t, которое будет хранится в стеке
 * \return              // "OUT_OF_MEMORY" - не хватает памяти под стек; EXIT_SUCCESS - стек успешно создан
 * конструктор стека
 */
int initArr(arrStack_t *ptr, size_t size_of_type) //>signature
{
    ptr->bot = malloc((unsigned)STACK_ARR_LEN * size_of_type);

    if (!ptr->bot)
        return OUT_OF_MEMORY;

    ptr->sizeOfField = size_of_type;
    ptr->top = ptr->bot + ptr->sizeOfField * STACK_ARR_LEN;
    ptr->curr = ptr->bot;
    ptr->stackLen = 0;

    return EXIT_SUCCESS;
}

// >documentation
/*!
 * \brief freeArr
 * \param ptr           // указатель ptr на переменную типа arrStack_t, адрес по которому получается доступ к стеку
 * деконструктор стека
 */
void freeArr(arrStack_t *ptr) //>signature
{
    free(ptr->bot);
}

// >documentation
/*!
 * \brief arrPush
 * \param ptr           // указатель ptr на переменную типа arrStack_t, адрес по которому можно будет получить доступ к стеку
 * \param item          // указатель item на переменную, из которой будет происходить запись значения на верх стека
 * \return              // STACK_OVERFLOW - стек переполнен, EXIT_SUCCESS - успешное исполнение
 * добавление элемента ptr на верх стека list из переменной по адресу item
 */
int arrPush(arrStack_t *ptr, void *item) //>signature
{
    if(ptr->curr == ptr->top)
    {
        printf("Stack overflow!\n");
        return STACK_OVERFLOW;
    }
    else
        ptr->curr += ptr->sizeOfField;

    memcpy(ptr->curr,item,ptr->sizeOfField);
    ptr->stackLen++;

    return EXIT_SUCCESS;
}

// >documentation
/*!
 * \brief arrPop
 * \param ptr           // указатель ptr на переменную типа arrStack_t, адрес по которому можно будет получить доступ к стеку
 * \param item          // указатель item на переменную, в которую будет происходить запись значения из стека
 * \return              // STACK_UNDERFLOW - стек пуст, EXIT_SUCCESS - успешное исполнение
 * удаление верхнего элемента стека и возвращает его в переменную по адресу item
 */
int arrPop(arrStack_t *ptr, void *item) //>signature
{
    if(ptr->curr == ptr->bot)
    {
        printf("Stack underflow!\n");
        return STACK_UNDERFLOW;
    }
    else
    {
        memcpy(item,ptr->curr,ptr->sizeOfField);
        ptr->curr -= ptr->sizeOfField;
    }
    ptr->stackLen--;
    return EXIT_SUCCESS;
}

// >documentation
/*!
 * \brief arrPeek
 * \param ptr           // указатель ptr на переменную типа arrStack_t, адрес по которому можно будет получить доступ к стеку
 * \param item          // указатель item на переменную, в которую будет происходить запись значения из стека
 * \return              // STACK_UNDERFLOW - стек пуст, EXIT_SUCCESS - успешное исполнение
 * просмотр верхнего элемента стека без удаления
 */
int arrPeek(arrStack_t *ptr, void *item) //>signature
{
    if(ptr->bot == ptr->curr)
    {
        printf("Stack underflow!\n");
        return STACK_UNDERFLOW;
    }
    memcpy(item, ptr->curr, ptr->sizeOfField);
    return EXIT_SUCCESS;
}

// >documentation
/*!
 * \brief arrStatus
 * \param ptr           // указатель ptr на переменную типа arrStack_t, адрес по которому можно будет получить доступ к стеку
 * выводит текущее состояние стека
 * указатель на нижнюю границу стека bot
 * указатель на верхнюю границу стека top
 * указатель на текущий первый пустой элемент стека сurr
 * текущую длину стека
 */
void arrStatus(arrStack_t * ptr) //>signature
{
    printf("Array status:\n");
    printf("Top = %p\n", ptr->top);
    printf("Bot = %p\n", ptr->bot);
    printf("Current = %p\n", ptr->curr);
    printf("Current lenght = %ld\n",(unsigned)(ptr->curr - ptr->bot)/ptr->sizeOfField);
}
