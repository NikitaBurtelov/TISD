#include "headers/record_routines.h"

/* >includes
"includes.h"
"types.h"
*/

int input_rec(record_t *rec) // >signature
{
    char buf[BUF_LEN];
    char strings[2][15];
    strcpy(strings[0], "group");
    strcpy(strings[1], "surname");

    char **pointers[2] = { &rec->group, &rec->surname };

    // Ввод группы и фамилии
    for(int i = 0; i < 2; i++)
    {
        printf("Input %s: ", strings[i]);
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

        if(!strlen(buf))
        {
            if(i)
                free(*pointers[0]);
            return EXIT_FAILURE;
        }

        char *pt = malloc(sizeof (char) * (strlen(buf) + 1));
        if(!pt)
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
    for(int i = 0; rec->surname[i]; i++)
        if(!('a' <= rec->surname[i] && rec->surname[i] <= 'z') && !('A' <= rec->surname[i] && rec->surname[i] <= 'Z'))
        {
            free(*pointers[0]);
            free(*pointers[1]);
            return EXIT_FAILURE;
        }

    // Ввод даты рождения
    int months[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    printf("Input date(YYYY.MM.DD): ");
    if(scanf("%d.%d.%d", &rec->date[0], &rec->date[1], &rec->date[2]) != 3 ||
            rec->date[0] < 1 || rec->date[1] > 12 || rec->date[1] < 1 || rec->date[2] < 1)
    {
        free(*pointers[0]);
        free(*pointers[1]);
        return EXIT_FAILURE;
    }

    if(!(rec->date[0] % 4))
        months[1]++;

    if(months[rec->date[1] - 1] < rec->date[2])
    {
        free(*pointers[0]);
        free(*pointers[1]);
        return EXIT_FAILURE;
    }


    // Ввод количества оценок
    printf("Input amount of marks: ");
    if(scanf("%d", &rec->marks_num) != 1 || rec->marks_num < 1)
    {
        free(*pointers[0]);
        free(*pointers[1]);
        return EXIT_FAILURE;
    }

    rec->marks = malloc(sizeof (double) * rec->marks_num);
    if(!rec->marks)
    {
        free(*pointers[0]);
        free(*pointers[1]);
        return EXIT_FAILURE;
    }

    // Ввод значений оценок
    printf("Input array of marks: ");
    for(int i = 0; i < rec->marks_num; i++)
        if(scanf("%lf", &rec->marks[i]) != 1 || rec->marks[i] < 0)
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
