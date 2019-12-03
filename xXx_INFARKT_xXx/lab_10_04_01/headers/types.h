#ifndef TYPES_H
#define TYPES_H

#define BUF_LEN 256

typedef struct
{
    char *surname;
    char *group;
    int date[3];
    int marks_num;
    double *marks;
} record_t;

typedef struct
{
    int len;
    record_t *data;
    char key; // GROUP == 1 // SURNAME == 2 // GRADE == 3
} record_arr_t;


#endif // TYPES_H
