#include "headers/rec_arr_routines.h"

/* >includes
"includes.h"
"types.h"
"record_routines.h"
*/

int init_arr(record_arr_t *arr) // >signature
{
    arr->key = arr->len = 0;
    arr->data = NULL;
    return EXIT_SUCCESS;
}

int dest_arr(record_arr_t *arr) // >signature
{
    for(int i = 0; i < arr->len; i++)
        dest_rec(&(arr->data[i]));

    free(arr->data);

    return EXIT_SUCCESS;
}

int add_rec(record_arr_t *arr, record_t rec) // >signature
{
    record_t *pt = realloc(arr->data, sizeof (record_t) * (arr->len + 1));
    if(!pt)
        return EXIT_FAILURE;
    arr->data = pt;

    arr->data[arr->len] = rec;

    arr->len++;
    return EXIT_SUCCESS;
}

int del_rec(record_arr_t *arr, int index) // >signature
{
    if(!arr->len)
        return EXIT_FAILURE;

    dest_rec(&arr->data[index]);

    for(int i = index; i < arr->len - 1; i++)
        arr->data[i] = arr->data[i+1];

    record_t *pt = realloc(arr->data, sizeof (record_t) * (arr->len - 1));
    if(!pt)
        return EXIT_FAILURE;
    arr->data = pt;

    arr->len--;

    return EXIT_SUCCESS;
}

int input_arr(record_arr_t *arr) // >signature
{
    record_t tmp;
    char buf[10];

    while(1)
    {
        int rc = input_rec(&tmp);
        if(rc == END_OF_INPUT)
            break;
        else if(rc == EXIT_FAILURE)
            return EXIT_FAILURE;
        if(add_rec(arr, tmp) != EXIT_SUCCESS)
            return EXIT_FAILURE;
        clear();
    }

    printf("Input key: ");
    fgets(buf, 10, stdin);
    if(strcmp(buf, "GROUP\n") == 0)
        arr->key = 1;
    else if(strcmp(buf, "SURNAME\n") == 0)
        arr->key = 2;
    else if(strcmp(buf, "GRADE\n") == 0)
        arr->key = 3;
    else
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int swap_rec(record_arr_t *arr, int i, int j) //>signature
{
    record_t tmp = arr->data[i];
    arr->data[i] = arr->data[j];
    arr->data[j] = tmp;
    return EXIT_SUCCESS;
}

int sort_arr(record_arr_t *arr) // >signature
{

    if(arr->key == 1)
    {
        for(int i = 0; i < arr->len - 1; i++)
            for(int j = 0; j < arr->len - i - 1; j++)
                if(strcmp(arr->data[j].group, arr->data[j+1].group) > 0)
                    swap_rec(arr, j, j+1);
    }
    else if(arr->key == 2)
    {
        for(int i = 0; i < arr->len - 1; i++)
            for(int j = 0; j < arr->len - i - 1; j++)
                if(strcmp(arr->data[j].surname, arr->data[j+1].surname) > 0)
                    swap_rec(arr, j, j+1);
    }
    else
    {
        for(int i = 0; i < arr->len - 1; i++)
            for(int j = 0; j < arr->len - i - 1; j++)
                if(1)
                    swap_rec(arr, j, j+1);
    }

    return EXIT_SUCCESS;
}

int older_then_17(int date[3]) //>signature
{
    const int yes = 1, no = 0;

    int day = 01, month = 11, year = 2019;

    day -= date[0];
    month += (day < 0 ? -1 : 0) - date[1];
    year += (month < 0 ? -1 : 0) - date[2];

    if (year > 17)
        return yes;
    else
        return no;
}

int b_task(record_arr_t *arr) // >signature
{
    for(int i = 0; i <arr->len; i++)
    {
        if(strcmp(arr->data[i].group, "ИУ7-31Б") == 0 && older_then_17(arr->data[i].date))
            del_rec(arr, i);
    }
    if(arr->len == 0)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int c_task(record_arr_t *arr) // >signature
{
    for(int i = 0; i < arr->len; i++)
    {
        record_t *tmp = &arr->data[i];
        for(int j = 0; j < tmp->marks_num; j++)
            if(tmp->marks[j] < 4.0)
            {
                for(int k = j; k < tmp->marks_num - 1; k++)
                    tmp->marks[k] = tmp->marks[k+1];
                tmp->marks_num--;
                j--;
            }
        if(tmp->marks_num == 0)
            return EXIT_FAILURE;
        double *pt = realloc(tmp->marks, sizeof (double) * tmp->marks_num);
        if(!pt)
            return EXIT_FAILURE;
        tmp->marks = pt;
    }
    return EXIT_SUCCESS;
}

int output_arr(record_arr_t *arr) // >signature
{
    printf("key=%d; len=%d;\n", arr->key, arr->len);
    for(int i = 0; i < arr->len ;i++)
    {
        record_t tmp = arr->data[i];
        printf("group=%s; surname=%s; date=%d.%d.%d; marks_num=%d;", tmp.group,
               tmp.surname, tmp.date[0], tmp.date[1], tmp.date[2], tmp.marks_num);
        for(int j = 0; j < tmp.marks_num; j++)
            printf("%.2lf  ", tmp.marks[j]);
        printf("\n");
    }
    return EXIT_SUCCESS;
}

int arr_to_file(record_arr_t *arr) // >signature
{
    FILE *fp;
    fp = fopen("students.txt", "w");

    if(!fp)
        return EXIT_FAILURE;

    for(int i = 0; i < arr->len ;i++)
    {
        record_t tmp = arr->data[i];
        fprintf(fp, "%s\n%s\n%d.%d.%d\n%d\n", tmp.group,
               tmp.surname, tmp.date[0], tmp.date[1], tmp.date[2], tmp.marks_num);
        for(int j = 0; j < tmp.marks_num; j++)
            fprintf(fp, "%lf  ", tmp.marks[j]);
        fprintf(fp, "\n");
    }

    fclose(fp);
    return EXIT_SUCCESS;
}

void clear() // >signature
{
  if(!feof(stdin))
    while ( getchar() != '\n' );
}
