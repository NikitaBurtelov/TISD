/*
This header file was generated automaticaly!
Generated at: 03 December 2019 (03.12.2019) At: 19:29:11
Amount of functions        : 13
Amount of documentated     : 0
All functions documentated : False
Amount of structures       : 0
Amount of enums            : 0
Function's names: 
   1 > add_rec
   2 > arr_to_file
   3 > b_task
   4 > c_task
   5 > clear
   6 > del_rec
   7 > dest_arr
   8 > init_arr
   9 > input_arr
  10 > older_then_17
  11 > output_arr
  12 > sort_arr
  13 > swap_rec

*/

#ifndef __REC_ARR_ROUTINES_H__
#define __REC_ARR_ROUTINES_H__

#include "record_routines.h"
#include "includes.h"
#include "types.h"



int init_arr(record_arr_t *arr);

int dest_arr(record_arr_t *arr);

int add_rec(record_arr_t *arr, record_t rec);

int del_rec(record_arr_t *arr, int index);

int input_arr(record_arr_t *arr);

int swap_rec(record_arr_t *arr, int i, int j);

int sort_arr(record_arr_t *arr);

int older_then_17(int date[3]);

int b_task(record_arr_t *arr);

int c_task(record_arr_t *arr);

int output_arr(record_arr_t *arr);

int arr_to_file(record_arr_t *arr);

void clear();

#endif // __REC_ARR_ROUTINES_H__

