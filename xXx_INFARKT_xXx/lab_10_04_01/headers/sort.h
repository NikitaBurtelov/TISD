/*
This header file was generated automaticaly!
Generated at: 09 December 2019 (09.12.2019) At: 00:05:23
Amount of functions        : 5
Amount of documentated     : 0
All functions documentated : False
Amount of structures       : 0
Amount of enums            : 0
Function's names: 
   1 > group_compare
   2 > marks_compare
   3 > sort_arr
   4 > surname_compare
   5 > swap_rec

*/

#ifndef __SORT_H__
#define __SORT_H__

#include "includes.h"
#include "types.h"



int swap_rec(record_arr_t *arr, int i, int j);

int group_compare(record_t *arg1, record_t *arg2);

int surname_compare(record_t *arg1, record_t *arg2);

int marks_compare(record_t *arg1, record_t *arg2);

int sort_arr(record_arr_t *arr);

#endif // __SORT_H__

