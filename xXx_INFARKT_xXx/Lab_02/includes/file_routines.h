#ifndef FILE_CDIO_H
#define FILE_CDIO_H

#include "types.h"

int my_fopen(FILE **fp, char *rc);

int read_rec(FILE *fp, str bufer);

int read_file(FILE *fp, car *car_list, int *len);

int save_changes(car *list, int len, flags flag);

#endif // FILE_CDIO_H
