#include "headers/record_routines.h"

/* >includes
"includes.h"
"types.h"
*/

int input_rec(record_t *rec) // >signature
{
    char buf[BUF_LEN];

    char **pointers[2] = { &rec->group, &rec->surname };

    // Ввод группы и фамилии
    for(int i = 0; i < 2; i++)
    {
        fgets(buf, BUF_LEN, stdin);
        buf[strlen(buf) - 1] = 0;

        if(!i && strlen(buf) == 4) // проверка на none
        {
            if((buf[0] == 'N' || buf[0] == 'n') &&
               (buf[1] == 'O' || buf[1] == 'o') &&
               (buf[2] == 'N' || buf[2] == 'n') &&
               (buf[3] == 'E' || buf[3] == 'e'))
                return END_OF_INPUT;
        }

        if(!strlen(buf)) // проверка на пустоту фамилии и группы
        {
            if(i)
                free(*pointers[0]);
            return EXIT_FAILURE;
        }

        char *pt = malloc(sizeof (char) * (strlen(buf) + 1));
        if(!pt) // проверка на выделении памяти под динамические строки
        {
            if(i)
                free(*pointers[0]);
            return EXIT_FAILURE;
        }
        else
        {
            *pointers[i] = pt;
            strcpy(*pointers[i], buf);
        }
    }

    // Проверка фамилии
    for(int i = 0; rec->surname[i]; i++) // проверка строка на валидность (символы [A-Za-z])
        if(!('a' <= rec->surname[i] && rec->surname[i] <= 'z') && !('A' <= rec->surname[i] && rec->surname[i] <= 'Z'))
        {
            free(*pointers[0]);
            free(*pointers[1]);
            return EXIT_FAILURE;
        }

    // Ввод даты рождения
    int months[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    char dates_str[3][256];

    fgets(buf, BUF_LEN, stdin);
    buf[strlen(buf) - 1] = 0;
    if(strlen(buf) != 10) // проверка на длину
    {
       free(*pointers[0]);
       free(*pointers[1]);
       return EXIT_FAILURE;
    }
    else
        for(int i = 0; i < 10; i++) // проверка на валидность символов
            if((i == 4 || i == 7) && buf[i] != '.')
            {
               free(*pointers[0]);
               free(*pointers[1]);
               return EXIT_FAILURE;
            }
            else if ((buf[i] < '0' || buf[i] > '9') && (i != 4 && i != 7))
            {
               free(*pointers[0]);
               free(*pointers[1]);
               return EXIT_FAILURE;
            }

    if(sscanf(buf ,"%[0-9].%[0-9].%[0-9]", dates_str[0], dates_str[1], dates_str[2]) != 3 || // проверка на валидность строки на тип YYYY.MM.DD
            strlen(dates_str[0]) != 4 || strlen(dates_str[1]) != 2 || strlen(dates_str[2]) != 2)
    {
        free(*pointers[0]);
        free(*pointers[1]);
        return EXIT_FAILURE;
    }
    else
    {
        int rc = 0;
        for(int i = 0; i < 3; i++) // считывание значений дат
            rc += sscanf(dates_str[i], "%d", &rec->date[i]);
        if (rc != 3 || rec->date[0] < 1 || rec->date[1] > 12 || rec->date[1] < 1 || rec->date[2] < 1 || rec->date[0] > 9999) // проверка на валидность значений дат
         {
            free(*pointers[0]);
            free(*pointers[1]);
            return EXIT_FAILURE;
        }
    }

    if(!(rec->date[0] % 4)) // учет високосного года
        months[1]++;

    if(months[rec->date[1] - 1] < rec->date[2]) // проверка на валидность значения DD
    {
        free(*pointers[0]);
        free(*pointers[1]);
        return EXIT_FAILURE;
    }


    // Ввод количества оценок
    if(scanf("%d", &rec->marks_num) != 1 || rec->marks_num < 1) // проверка валидности значения длины массива
    {
        free(*pointers[0]);
        free(*pointers[1]);
        return EXIT_FAILURE;
    }

    rec->marks = malloc(sizeof (double) * (unsigned)rec->marks_num);
    if(!rec->marks) // проверка на выделение памяти
    {
        free(*pointers[0]);
        free(*pointers[1]);
        return EXIT_FAILURE;
    }

    // Ввод значений оценок
    for(int i = 0; i < rec->marks_num; i++)
        if(scanf("%lf", &rec->marks[i]) != 1 || rec->marks[i] < 0) // проверка валидности значения длины массива
        {
            free(*pointers[0]);
            free(*pointers[1]);
            free(rec->marks);
            return EXIT_FAILURE;
        }

    return EXIT_SUCCESS;
}

int dest_rec(record_t *rec) // >signature
{
    free(rec->group);
    free(rec->marks);
    free(rec->surname);
    rec->group = rec->surname = NULL;
    rec->marks = NULL;
    return EXIT_SUCCESS;
}
