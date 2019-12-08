#include "headers/sort.h"

/* >includes
"types.h"
"includes.h"
*/

int swap_rec(record_arr_t *arr, int i, int j) //>signature
{
    record_t tmp = arr->data[i];
    arr->data[i] = arr->data[j];
    arr->data[j] = tmp;
    return EXIT_SUCCESS;
}

int group_compare(record_t *arg1, record_t *arg2) //>signature
{
    int res = strcmp(arg1->group, arg2->group);
    if(res > 0) return 1;
    else if(res == 0) return 0;
    else return -1;
}

int surname_compare(record_t *arg1, record_t *arg2) //>signature
{
    int res = strcmp(arg1->surname, arg2->surname);
    if(res > 0) return 1;
    else if(res == 0) return 0;
    else return -1;
}

int marks_compare(record_t *arg1, record_t *arg2) //>signature
{
    double avg1 = 0, avg2 = 0;
    for(int i = 0; i < arg1->marks_num; i++)
        avg1 += arg1->marks[i];
    for(int i = 0; i < arg2->marks_num; i++)
        avg2 += arg2->marks[i];
    avg1 /= arg1->marks_num;
    avg2 /= arg2->marks_num;
    if(avg1 > avg2) return 1;
    else if(avg1 < avg2) return -1;
    else return 0;
}

int sort_arr(record_arr_t *arr) // >signature
{
    int (*compare) (record_t *, record_t *);
    if(arr->key == 1)
        compare = group_compare;
    else if(arr->key == 2)
        compare = surname_compare;
    else
        compare = marks_compare;

    for(int i = 0; i < arr->len - 1; i++)
        for(int j = 0; j < arr->len - i - 1; j++)
            if(compare(&arr->data[j], &arr->data[j+1]) > 0)
                swap_rec(arr, j, j+1);

    return EXIT_SUCCESS;
}
