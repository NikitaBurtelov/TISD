/*
This header file was generated automaticaly!
Generated at: 03 December 2019 (03.12.2019) At: 14:51:28
Amount of functions        : 6
Amount of documentated     : 6
All functions documentated : True
Amount of structures       : 1
Amount of enums            : 0
Function's names: 
   1 > arrPeek
   2 > arrPop
   3 > arrPush
   4 > arrStatus
   5 > freeArr
   6 > initArr

*/

#ifndef __STACKARRROUTINES_H__
#define __STACKARRROUTINES_H__

#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>

#define STACK_ARR_LEN 6
#define OUT_OF_MEMORY -100
#define STACK_OVERFLOW -101
#define STACK_UNDERFLOW -102


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

/*!
* \brief initArr
* \param ptr           // указатель ptr на переменную типа arrStack_t, адрес по которому можно будет получить доступ к стеку
* \param size_of_type  // размер size_of_type 1 значения типа size_t, которое будет хранится в стеке
* \return              // "OUT_OF_MEMORY" - не хватает памяти под стек; EXIT_SUCCESS - стек успешно создан
* конструктор стека
*/
int initArr(arrStack_t *ptr, size_t size_of_type);

/*!
* \brief freeArr
* \param ptr           // указатель ptr на переменную типа arrStack_t, адрес по которому получается доступ к стеку
* деконструктор стека
*/
void freeArr(arrStack_t *ptr);

/*!
* \brief arrPush
* \param ptr           // указатель ptr на переменную типа arrStack_t, адрес по которому можно будет получить доступ к стеку
* \param item          // указатель item на переменную, из которой будет происходить запись значения на верх стека
* \return              // STACK_OVERFLOW - стек переполнен, EXIT_SUCCESS - успешное исполнение
* добавление элемента ptr на верх стека list из переменной по адресу item
*/
int arrPush(arrStack_t *ptr, void *item);

/*!
* \brief arrPop
* \param ptr           // указатель ptr на переменную типа arrStack_t, адрес по которому можно будет получить доступ к стеку
* \param item          // указатель item на переменную, в которую будет происходить запись значения из стека
* \return              // STACK_UNDERFLOW - стек пуст, EXIT_SUCCESS - успешное исполнение
* удаление верхнего элемента стека и возвращает его в переменную по адресу item
*/
int arrPop(arrStack_t *ptr, void *item);

/*!
* \brief arrPeek
* \param ptr           // указатель ptr на переменную типа arrStack_t, адрес по которому можно будет получить доступ к стеку
* \param item          // указатель item на переменную, в которую будет происходить запись значения из стека
* \return              // STACK_UNDERFLOW - стек пуст, EXIT_SUCCESS - успешное исполнение
* просмотр верхнего элемента стека без удаления
*/
int arrPeek(arrStack_t *ptr, void *item);

/*!
* \brief arrStatus
* \param ptr           // указатель ptr на переменную типа arrStack_t, адрес по которому можно будет получить доступ к стеку
* выводит текущее состояние стека
* указатель на нижнюю границу стека bot
* указатель на верхнюю границу стека top
* указатель на текущий первый пустой элемент стека сurr
* текущую длину стека
*/
void arrStatus(arrStack_t * ptr);

#endif // __STACKARRROUTINES_H__

