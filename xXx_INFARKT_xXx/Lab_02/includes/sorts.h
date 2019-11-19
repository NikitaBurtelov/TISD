#ifndef SORTS_H
#define SORTS_H

#include "types.h"

void save_key(key *from, key *to);

double shell_key_sort(int len, key *list);

double buble_key_sort(int len, key *list);

void save_car(car *from, car *to);

double shell_car_sort(int len, car *list);

double buble_car_sort(int len, car *list);

void shuffle_car_list(car *list, int len);

void shuffle_key_list(key *list, int len);

#endif
