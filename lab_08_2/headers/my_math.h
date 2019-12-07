#ifndef MY_MATH_H
#define MY_MATH_H

#include "includes.h"
#include "array_routines.h"

// Выполняет подсчет значения μ1
int mu1_foo(arr_t p, int len, double *mu1);

// Выполняет подсчет значения μ2
int mu2_foo(arr_t p, int len, double *mu2);

// Сортировка массива значений по возрастанию
void my_sort(arr_t p, int len);

// Удаляет из массива любой элемент х, где |х| > |μ1|
int form_a1(arr_t *p, int *len, double mu1);

#endif // MY_MATH_H
