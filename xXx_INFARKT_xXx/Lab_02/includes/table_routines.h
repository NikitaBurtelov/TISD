#ifndef STD_CDIO_H
#define STD_CDIO_H

#include "types.h"

int strprs(str bufer, car *new_car);

void print_elem(car my_car);

void print_cars(car *car_list);

int add_rec(car *list, flags *flag, int *len);

int choose_feild(int *field);

int input_field_value(int field, choose *field_value);

void delete_rec(int field, car *my_car, choose field_value);

int delete_procedure(key *key_list, car *car_list, int *car_list_len, int *key_list_len);

void fill_keys(key *key_list, car *car_list, int *car_list_len, int *key_list_len);

void print_keys(key *key_list, int key_list_len);

void print_table_by_keys(car *car_list, int car_list_len, key *key_list, int key_list_len);

void clear(void);

#endif // STD_CDIO_H
