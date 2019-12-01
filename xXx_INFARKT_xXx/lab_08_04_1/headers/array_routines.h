#ifndef CDIO_H

#define CDIO_H

#include "includes.h"

int create_arr(void **p, int len, size_t size_of_type);

int recreate_arr(void **p, int new_len, size_t size_of_type);

int delete_arr(void **p);

int arr_in(arr_t p, int len);

void insert(arr_t p, int *len, double elem, int pos);

void arr_out(arr_t p, int len);

#endif // CDIO_H
