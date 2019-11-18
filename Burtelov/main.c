/**
 * @mainpage Отчте к лабораторной работе №2
 * @brief Работу выполнил: \n
 * @brief Студент группы ИУ7-33Б \n
 * @brief Буртелов Никита \n
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/*!@param STRUCT_LEN макстмальный размер массива структур*/
#define STRUCT_LEN 70
/*!@param MENU_LEN количество пунктов в меню*/
#define MENU_LEN 6
/*!@param POS_LEN количество позиций для дальнейшего парсинга*/
#define POS_LEN 8
/*!@param BUF_LEN максимальный размер буфера*/
#define BUF_LEN 100
/*!@param CHAR_LEN максимальный размер массива символа*/
#define CHAR_LEN 30
/*!@param AMOUNT_SORT кол-во сортировок*/
#define AMOUNT_SORT 10000
#define EXIT_FAILURE_DEL -1

/*!
    @param BUFER[BUF_LEN]  буфер
*/

typedef char BUFER[BUF_LEN];

/*!
    @param POS_PARS[POS_LEN] массив, содержащий позиции запятых для парсинга строки
*/

typedef short int POS_PARS[POS_LEN];

/*!@brief Структура, предназначенная для обработки данных об автомобилях*/
typedef struct
{
    /*!@brief Модель машины*/
    char model[CHAR_LEN];
    /*!@brief Страна-производитель*/
    char country[CHAR_LEN];
    /*!@brief Цвет*/
    char color[CHAR_LEN];
    /*!@brief Цена*/
    int cost;
    /*!@brief Состояние 1 - б/у, 0 - нет*/
    int state;
    /*!@brief Флаг на удаление*/
    int flag_del;

    union
    {
        struct
        {
            /*!@brief Гарантия*/
            int guar;
        } /*!@brief Структура, для новых автомобилей*/
        car_new;

        struct
        {
            /*!@brief Год выпуска*/
            int year;
            /*!@brief Пробег*/
            int mileage;
            /*!@brief Кол-во ремонтов*/
            int repairs;
            /*!@brief Кол-во владельцев*/
            int owner;
        }/*!@brief Структура, для б.у. автомобилей*/
        car_used;
    }/*!@brief Union, включающий в себя дополнительный сведения об автомобилях*/
    condition;
}car;

/*!@brief Структура ключей*/
typedef struct {
    /*!@brief Name*/
    int name;
    /*!@brief id*/
    int id;
    /*!@brief Флаг удаления*/
    int flag_del_sort;
} car_sort;

/*!@brief Инициализация не отсортированной струкртуры ключей, */
/*!
 * @param *s - указатель на массив структур-ключей
 * @param *s_not - указатель на не отстортированный массив структур-ключей
*/
void car_hb(car_sort *s, car_sort *s_not, int len_struct)
{
    for (int i = 0; i < len_struct; i++)
    {
        s_not[i].name = s[i].name;
        s_not[i].id = s[i].id;
    }
}
/*!@brief Инициализация исходной не отсортированной структуры */
/*!
 * @param *p - указатель на массив структур-ключей
 * @param *p_not - указатель на не отстортированный массив структур
*/
void car_dont_hb(car *p, car *p_not, int len_struct)
{
    for (int j = 0; j < len_struct; j++)
    {
        strcpy(p_not[j].model, p[j].model);
        strcpy(p_not[j].country, p[j].country);
        strcpy(p_not[j].color, p[j].color);
        p_not[j].cost = p[j].cost;
        p_not[j].flag_del = p[j].flag_del;
        p_not[j].condition.car_new.guar = p[j].condition.car_new.guar;
        p_not[j].condition.car_used.year = p[j].condition.car_used.year;
        p_not[j].condition.car_used.mileage = p[j].condition.car_used.mileage;
        p_not[j].condition.car_used.repairs = p[j].condition.car_used.repairs;
        p_not[j].condition.car_used.owner = p[j].condition.car_used.owner;
        p_not[j].state = p[j].state;
    }
}

/*!@brief Возращение структуры ключей к не отсортированному виду*/
void car_sort_init_frst(car_sort *s, car_sort *s_not, int len_struct)
{
    for (int i = 0; i < len_struct; i++)
    {
        s[i].name = s_not[i].name;
        s[i].id = s_not[i].id;
    }
}

/*!@brief Идентификайия структуры для дальнейшего заполнения*/
void ident_struct(car  *p)
{
    for (int j = 0; j < CHAR_LEN; j++)
    {
        p->model[j] = '\0';
        p->color[j] = '\0';
        p->country[j] = '\0';
    }
    p->cost = 0;
    p->state = -1;
    p->condition.car_used.year = 0;
    p->condition.car_new.guar = 0;
    p->condition.car_used.owner = 0;
    p->condition.car_used.repairs = 0;
    p->condition.car_used.mileage = 0;
    p->flag_del = 0;
}

/*!@brief Идентификация буфера*/
void ident_buf(BUFER buf)
{
    for (int i = 0; i < BUF_LEN; i++)
        buf[i] = '\0';
}

/*!@brief Нахождение позиции запятой, для дальнейшего парсинга строки*/
 void ident_pos(POS_PARS pos_pars)
{
    for (int i = 0; i < POS_LEN; i++)
        pos_pars[i] = 0;
}

/*!@brief Вывод меню при выборе удаления полей структуры*/
void del_struct_record_menu()
{
    printf("Choose which field we will delete: \n"); //Выбор поля удаления
    printf("1. Model\n");
    printf("2. Country\n");
    printf("3. Color\n");
    printf("4. Cost\n");
    printf("5. State\n");
    printf("6. Guar\n");
    printf("7. Year\n");
    printf("8. Mileage\n");
    printf("9. Repairs\n");
    printf("10. Owner\nInput number: ");
}

/*!@brief Печать ключей*/
void printf_result_sort(car *p,car_sort *p_s, int len_struct)
{
    printf("  Id        Cost");
    printf("\n___________________");
    for (int i = 0; i < len_struct; i++)
    {
        if (p[p_s[i].id].flag_del == 0)
        {
            printf("\n%5d   |%8d |", p_s[i].id, p_s[i].name);
        }
    }
    printf("\n___________________\n");
}

/*!@brief Сортировка структуры ключей методом пузырька*/
void sort_struct_bubble(car_sort *s, int len_struct)
{
    int tmp, tmp_id;

    for (int i = 0; i < len_struct - 1; i++)
    {
        for (int j = 0; j < len_struct - i - 1; j++)
        {
            if (s[j].name > s[j + 1].name)
            {
                tmp = s[j].name;
                tmp_id = s[j].id;
                s[j].name = s[j + 1].name;
                s[j].id = s[j + 1].id;
                s[j + 1].id = tmp_id;
                s[j + 1].name = tmp;
            }
        }
    }
}

/*!@brief Сортировка структуры ключей методом Шелла*/
void sort_struct_quick(car_sort *s, int len_struct)
{
    int i, j, step;
    int tmp, tmp_id;

    for (step = len_struct / 2; step > 0; step /= 2)
    {
        for (i = step; i < len_struct; i++)
        {
            tmp = s[i].name;
            tmp_id = s[i].id;

            for ( j = i; j >= step; j -= step)
            {
                if (tmp < s[j - step].name)
                {
                    s[j].name = s[j - step].name;
                    s[j].id = s[j - step].id;
                }

                else
                    break;
            }
            s[j].name = tmp;
            s[j].id = tmp_id;
        }
    }
}

/*!@brief Функция поиска совпадений в полях структуры при удалении*/
int del_struct_search(car *p, BUFER buf, int record)
{
    short flag_y = 0, flag_n = 1;
    int buf_int = 0;
    if (record >= 5)
        buf_int = atoi(buf);

    if (record == 1)
    {
        if (strcmp(p->model, buf) == 0)
            return flag_y;
        else
            return flag_n;
    }
    else if (record == 2)
    {
        if (strcmp(p->country, buf) == 0)
            return flag_y;
        else
            return flag_n;
    }
    else if (record == 3)
    {
        if (strcmp(p->color, buf) == 0)
            return flag_y;
        else
            return flag_n;
    }
    else if (record == 4)
    {
        if (p->cost == buf_int)
            return flag_y;
        else
            return flag_n;
    }
    else if (record == 5)
    {
        if (p->state == buf_int)
            return flag_y;
        else
            return flag_n;
    }
    else if (record == 6)
    {
        if (p->condition.car_new.guar == buf_int)
            return flag_y;
        else
            return flag_n;
    }
    else if (record == 7)
    {
        if (p->condition.car_used.year == buf_int)
            return flag_y;
        else
            return flag_n;
    }
    else if (record == 8)
    {
        if (p->condition.car_used.mileage == buf_int)
            return flag_y;
        else
            return flag_n;
    }
    else if (record == 9)
    {
        if (p->condition.car_used.repairs == buf_int)
            return flag_y;
        else
            return flag_n;
    }
    else if (record == 10)
    {
        if (p->condition.car_used.owner == buf_int)
            return flag_y;
        else
            return flag_n;
    }
    else
        return EXIT_FAILURE_DEL;
}

/*!@brief Удаление полей записи в массиве структур*/
int del_struct_record(car *p, int *len_struct)
{
    long number_menu;
    char buf_del[BUF_LEN];
    char str_menu[10][CHAR_LEN];
    int number_int = 0;

    ident_buf(buf_del);

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < CHAR_LEN; j++)
            str_menu[i][j] = '\0';
    }

    strcpy(str_menu[0], "Model");
    strcpy(str_menu[1], "Country");
    strcpy(str_menu[2], "Color");
    strcpy(str_menu[3], "Cost");
    strcpy(str_menu[4], "State");
    strcpy(str_menu[5], "Guar");
    strcpy(str_menu[6], "Year");
    strcpy(str_menu[7], "Mileage");
    strcpy(str_menu[8], "Repairs");
    strcpy(str_menu[9], "Owner");

    del_struct_record_menu();

    if (scanf("%s", buf_del) != 1)
    {
        puts("\nERROR");
        return EXIT_FAILURE;
    }

    number_menu = atoi(buf_del);

    if (number_menu) {
        ident_buf(buf_del);

        printf("\nInput %s \n", str_menu[number_menu - 1]);

        scanf(" %[^\n]s", buf_del);

        printf("BUFER %s, N %ld", buf_del, number_menu);

        for (int i = 0; i < STRUCT_LEN; i++)
        {
            if (del_struct_search(&p[i], buf_del, number_menu) == 0) {
                p[i].flag_del = 1;
            }
        }
    }
    else
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

/*!@brief Добавление новых элементов в массив структур*/
int append_struct(car *p, car_sort *s, int *len_struct)
{
    char buf_state = 0;
    int index;

    index = *len_struct;

    if (*len_struct == STRUCT_LEN)
    {
        for (int i = 0; i < STRUCT_LEN; i++)
        {
            if (p[i].flag_del == 1)
            {
                index = i;
                break;
            }

        }
    }
    
    printf("Input model auto: ");
    scanf("%s", p[index].model);

    printf("Input country: ");
    scanf("%s", p[index].country);

    printf("Input color: ");
    scanf("%s", p[index].color);

    printf("Input cost: ");
    scanf("%d", &p[index].cost);

    printf("Input state (y/n): ");
    scanf("%s", &buf_state);

    if (buf_state == 'y')
    {
        p[index].state = 0;
        printf("Input guar: ");
        scanf("%d", &p[index].condition.car_new.guar);
    }
    else if (buf_state == 'n')
    {
        p[index].state = 1;

        printf("Input year: ");
        scanf("%d", &p[index].condition.car_used.year);

        printf("Input milleage: ");
        scanf("%d", &p[index].condition.car_used.mileage);

        printf("Input repairs: ");
        scanf("%d", &p[index].condition.car_used.repairs);

        printf("Input owner: ");
        scanf("%d", &p[index].condition.car_used.owner);
    }
    else
        return EXIT_FAILURE;

    *len_struct = *len_struct + 1;

    s[index].id = index;
    s[index].name = p[index].cost;

    return EXIT_SUCCESS;
}

void print_len(car *p, short *len_model, short *len_country, short *len_color, short *len_cost, int len_struct)
{
    short len_model_now, len_country_now, len_color_now;
    for (int i  = 0; i < len_struct; i++)
    {
        len_model_now = (short) strlen(p[i].model);
        len_country_now = (short) strlen(p[i].country);
        len_color_now = (short) strlen(p[i].color);

        if (len_model_now > *len_model)
            *len_model = len_model_now;

        if (len_country_now > *len_country)
            *len_country = len_country_now;

        if (len_color_now > *len_color)
            *len_color = len_color_now;
    }
}

/*!@brief Сортировка массива структур методом пузырька*/
void sort_dont_key_bubble(car *p, int len_struct)
{
    int tmp_cost,  tmp_state, tmp_del; //общие параметры
    int tmp_guar; //car_new
    int tmp_year, tmp_mil, tmp_rep, tmp_owner; // car_used

    char tmp_model[CHAR_LEN], tmp_country[CHAR_LEN], tmp_color[CHAR_LEN];

    for (int i = 0; i < CHAR_LEN; i++)
    {
        tmp_model[i] = '\0';
        tmp_country[i] = '\0';
        tmp_color[i] = '\0';
    }

    for (int i = 0; i < len_struct - 1; i++)
    {
        for (int j = 0; j < len_struct - i - 1; j++)
        {
            if (p[j].cost > p[j + 1].cost)
            {
                strcpy(tmp_model, p[j].model);
                strcpy(tmp_country, p[j].country);
                strcpy(tmp_color, p[j].color);
                tmp_cost = p[j].cost;
                tmp_del = p[j].flag_del;
                tmp_state = p[j].state;
                tmp_guar = p[j].condition.car_new.guar;
                tmp_year = p[j].condition.car_used.year;
                tmp_mil = p[j].condition.car_used.mileage;
                tmp_rep = p[j].condition.car_used.repairs;
                tmp_owner = p[j].condition.car_used.owner;

                p[j].cost = p[j + 1].cost;
                p[j].flag_del = p[j + 1].flag_del;
                strcpy(p[j].model, p[j + 1].model);
                strcpy(p[j].country, p[j + 1].country);
                strcpy(p[j].color, p[j + 1].color);
                p[j].state = p[j + 1].state;
                p[j].condition.car_new.guar = p[j + 1].condition.car_new.guar;
                p[j].condition.car_used.year = p[j + 1].condition.car_used.year;
                p[j].condition.car_used.mileage = p[j + 1].condition.car_used.mileage;
                p[j].condition.car_used.repairs = p[j + 1].condition.car_used.repairs;
                p[j].condition.car_used.owner = p[j + 1].condition.car_used.owner;

                p[j + 1].cost = tmp_cost;
                p[j + 1].flag_del = tmp_del;
                strcpy(p[j + 1].model, tmp_model);
                strcpy(p[j + 1].country, tmp_country);
                strcpy(p[j + 1].color, tmp_color);
                p[j + 1].state = tmp_state;
                p[j + 1].condition.car_new.guar = tmp_guar;
                p[j + 1].condition.car_used.year = tmp_year;
                p[j + 1].condition.car_used.mileage = tmp_mil;
                p[j + 1].condition.car_used.repairs = tmp_rep;
                p[j + 1].condition.car_used.owner = tmp_owner;
            }
        }
    }
}

/*!@brief Сортировка массива структур методом Шелла*/
void sort_dont_key_quick(car *p, int len_struct)
{
    int i, j, step;
    int tmp,  tmp_state, tmp_del; //общие параметры
    int tmp_guar; //car_new
    int tmp_year, tmp_mil, tmp_rep, tmp_owner; // car_used

    char tmp_model[CHAR_LEN], tmp_country[CHAR_LEN], tmp_color[CHAR_LEN];

    for (step = len_struct / 2; step > 0; step /= 2)
    {
        for (i = step; i < len_struct; i++)
        {
            strcpy(tmp_model, p[i].model);
            strcpy(tmp_country, p[i].country);
            strcpy(tmp_color, p[i].color);
            tmp = p[i].cost;
            tmp_del = p[i].flag_del;
            tmp_state = p[i].state;
            tmp_guar = p[i].condition.car_new.guar;
            tmp_year = p[i].condition.car_used.year;
            tmp_mil = p[i].condition.car_used.mileage;
            tmp_rep = p[i].condition.car_used.repairs;
            tmp_owner = p[i].condition.car_used.owner;


            for ( j = i; j >= step; j -= step)
            {
                if (tmp < p[j - step].cost)
                {
                    p[j].cost = p[j - step].cost;
                    p[j].flag_del = p[j - step].flag_del;
                    strcpy(p[j].model, p[j - step].model);
                    strcpy(p[j].country, p[j - step].country);
                    strcpy(p[j].color, p[j - step].color);
                    p[j].condition.car_new.guar = p[j - step].condition.car_new.guar;
                    p[j].condition.car_used.year = p[j - step].condition.car_used.year;
                    p[j].condition.car_used.mileage = p[j - step].condition.car_used.mileage;
                    p[j].condition.car_used.repairs = p[j - step].condition.car_used.repairs;
                    p[j].condition.car_used.owner = p[j - step].condition.car_used.owner;
                    p[j].state = p[j - step].state;
                }
                else
                    break;
            }
            p[j].cost = tmp;
            p[j].flag_del = tmp_del;
            strcpy(p[j].model, tmp_model);
            strcpy(p[j].country, tmp_country);
            strcpy(p[j].color, tmp_color);
            p[j].condition.car_new.guar = tmp_guar;
            p[j].condition.car_used.year = tmp_year;
            p[j].condition.car_used.mileage = tmp_mil;
            p[j].condition.car_used.repairs = tmp_rep;
            p[j].condition.car_used.owner = tmp_owner;
            p[j].state = tmp_state;
        }
    }
}

/*!@brief Печать таблицы, содержащий поля массива структур*/
void print_struct_sort(car *p, car_sort *s, int len_struct)
{
// max длина слова полей структур
    short int len_model = 0, len_country = 0, len_color = 0, len_cost = 0;
    short int flag_tabl =  1, flag_head = 1;
    char param[CHAR_LEN];

    for (int i = 0; i < CHAR_LEN; i++)
        param[i] = '\0';

    print_len(p, &len_model, &len_country, &len_color, &len_cost, len_struct);

    printf("\n");

    for (int i = 0; i < 106; i++)
        printf("_");

    for (int j = -1; j < len_struct; j++) {

        if (p[s[j].id].flag_del != 1) {
            if (!flag_tabl) {
                printf("\n");
                for (int i = 0; i < 18; i++)
                    printf("_");
                printf("|");

                for (int i = 0; i < 12; i++)
                    printf("_");
                printf("|");

                for (int i = 0; i < 11; i++)
                    printf("_");
                printf("|");

                for (int i = 0; i < 11; i++)
                    printf("_");
                printf("|");

                for (int i = 0; i < 7; i++)
                    printf("_");
                printf("|");

                for (int i = 0; i < 5; i++)
                    printf("_");
                printf("|");

                for (int i = 0; i < 7; i++)
                    printf("_");
                printf("|");

                for (int i = 0; i < 10; i++)
                    printf("_");
                printf("|");

                for (int i = 0; i < 9; i++)
                    printf("_");
                printf("|");

                for (int i = 0; i < 6; i++)
                    printf("_");

                printf("|");
            }

            if (flag_head == 0) {
                printf("\n%17s |", p[s[j].id].model);

                printf("%11s |", p[s[j].id].country);

                printf("%10s |", p[s[j].id].color);

                printf("%10d |", p[s[j].id].cost);

                if (p[s[j].id].state == 1) {
                    printf("%6s |", "Used");

                    printf(" %3s |", "---");

                    printf("%6d |", p[s[j].id].condition.car_used.year);

                    printf("%9d |", p[s[j].id].condition.car_used.mileage);

                    printf("%8d |", p[s[j].id].condition.car_used.repairs);

                    printf("%5d |", p[s[j].id].condition.car_used.owner);


                } else {
                    printf("%6s |", "New");

                    printf("%3d  |", p[s[j].id].condition.car_new.guar);

                    printf("%5s  |%7s   |%6s   |%4s  |", "---", "---", "---", "---");
                }

            }
            else
            {
                printf("\n%14s    |%10s  |%9s  |%9s  |%4s  |%5s|%6s |%9s |%8s | %5s|",
                       "Model", "Country", "Color", "Cost", "State","Guar.", "Year", "Mileage",
                       "Repairs", "Owner");
            }
            flag_head = 0;
            flag_tabl = 0;
        }
    }
    printf("\n__________________|____________|___________|_"
           "__________|_______|_____|_______|___"
           "_______|_________|______|\n");
}

/*!@brief Печать времени сортировок массива структур и массива ключей */
void print_result(clock_t shell1, clock_t shell2, clock_t bubble1, clock_t bubble2
                  ,clock_t shell3, clock_t shell4, clock_t bubble3, clock_t bubble4)
{
    printf("Sort times are based on 10,000 sorts.");
    printf("\n____________________________________\n");
    printf("         |    Shell   |    Bubble  |\n");
    printf("_________|____________|____________|\n");
    printf(" Key     | %.8lf |", (double) (shell2 - shell1) / CLOCKS_PER_SEC);
    printf(" %.8lf |\n", (double) (bubble2 - bubble1) / CLOCKS_PER_SEC);
    printf("_________|____________|____________|\n");
    printf(" Struct  | %.8lf |", (double) (shell4 - shell3) / CLOCKS_PER_SEC);
    printf(" %.8lf |\n", (double) (bubble4 - bubble3) / CLOCKS_PER_SEC);
    printf("_________|____________|____________|\n");

    printf("Structure size: 118 Kbyte\n70 element structure size: 8260 Kbyte\n");
}

/*!@brief Печать таблицы данных*/
void print_struct(car *p, int len_struct) {
    // max длина слова полей структур
    short int len_model = 0, len_country = 0, len_color = 0, len_cost = 0;
    short int flag_tabl =  1, flag_head = 1;
    char param[CHAR_LEN];

    for (int i = 0; i < CHAR_LEN; i++)
        param[i] = '\0';

    print_len(p, &len_model, &len_country, &len_color, &len_cost, len_struct);

    printf("\n");

    for (int i = 0; i < 106; i++)
        printf("_");

    for (int j = -1; j < len_struct; j++) {

        if (p[j].flag_del != 1) {
            if (!flag_tabl) {
                printf("\n");
                for (int i = 0; i < 18; i++)
                    printf("_");
                printf("|");

                for (int i = 0; i < 12; i++)
                    printf("_");
                printf("|");

                for (int i = 0; i < 11; i++)
                    printf("_");
                printf("|");

                for (int i = 0; i < 11; i++)
                    printf("_");
                printf("|");

                for (int i = 0; i < 7; i++)
                    printf("_");
                printf("|");

                for (int i = 0; i < 5; i++)
                    printf("_");
                printf("|");

                for (int i = 0; i < 7; i++)
                    printf("_");
                printf("|");

                for (int i = 0; i < 10; i++)
                    printf("_");
                printf("|");

                for (int i = 0; i < 9; i++)
                    printf("_");
                printf("|");

                for (int i = 0; i < 6; i++)
                    printf("_");

                printf("|");
            }

            if (flag_head == 0) {
                printf("\n%17s |", p[j].model);

                printf("%11s |", p[j].country);

                printf("%10s |", p[j].color);

                printf("%10d |", p[j].cost);

                if (p[j].state == 1) {
                    printf("%6s |", "Used");

                    printf(" %3s |", "---");

                    printf("%6d |", p[j].condition.car_used.year);

                    printf("%9d |", p[j].condition.car_used.mileage);

                    printf("%8d |", p[j].condition.car_used.repairs);

                    printf("%5d |", p[j].condition.car_used.owner);


                } else {
                    printf("%6s |", "New");

                    printf("%3d  |", p[j].condition.car_new.guar);

                    printf("%5s  |%7s   |%6s   |%4s  |", "---", "---", "---", "---");
                }

            }
            else
            {
                printf("\n%14s    |%10s  |%9s  |%9s  |%4s  |%5s|%6s |%9s |%8s | %5s|",
                        "Model", "Country", "Color", "Cost", "State","Guar.", "Year", "Mileage",
                        "Repairs", "Owner");
            }
            flag_head = 0;
            flag_tabl = 0;

        }
     }
    printf("\n__________________|____________|___________|_"
           "__________|_______|_____|_______|___"
           "_______|_________|______|\n");

}

/*!@brief Парсинг строк из файла*/
int parser(car *p, car_sort *s, BUFER buf){
    // Позиция запятой
    POS_PARS pos_pars;
    // Счетчик
    short int x = 0, pos_i = 0, ind_str = 0;
    // малый буфер
    BUFER buf_min;

    ident_buf(buf_min);

    ident_pos(pos_pars);

    while(buf[x] != '\n')
    {
        if (buf[x] == ',') {
            pos_pars[pos_i] = x;
            pos_i++;
        }
        x++;
    if (buf[x] == '\n')
        break;
    }

    for (int i = 0; i < pos_pars[0]; i++)
        p->model[i] = buf[i];

    for (int i = pos_pars[0] + 1, j = 0; i < pos_pars[1]; i++, j++)
        p->country[j] = buf[i];

    for (int i = pos_pars[1] + 1, j = 0; i < pos_pars[2]; i++, j++)
        buf_min[j] = buf[i];

    p->cost = atoi(buf_min);
    s->name = p->cost;

    ident_buf(buf_min);

    for (int i = pos_pars[2] + 1, j = 0; i < pos_pars[3]; i++, j++)
        p->color[j] = buf[i];

    if ((buf[pos_pars[3] + 2]) == '1') {
        p->state = 1;
        for (int i = pos_pars[4] + 1, j = 0; i < pos_pars[5]; i++, j++)
            buf_min[j] = buf[i];

        p->condition.car_used.year = atoi(buf_min);
        ident_buf(buf_min);

        for (int i = pos_pars[5] + 1, j = 0; i < pos_pars[6]; i++, j++)
            buf_min[j] = buf[i];

        p->condition.car_used.mileage = atoi(buf_min);
        ident_buf(buf_min);

        for (int i = pos_pars[6] + 1, j = 0; i < pos_pars[7]; i++, j++)
            buf_min[j] = buf[i];

        p->condition.car_used.repairs = atoi(buf_min);
        ident_buf(buf_min);

        for (int i = pos_pars[7] + 1, j = 0; i < strlen(buf); i++, j++)
            buf_min[j] = buf[i];
        p->condition.car_used.owner = atoi(buf_min);
        ident_buf(buf_min);
        }
    else
    {
        p->state = 0;

        for (int i = pos_pars[4] + 1, j = 0; i < strlen(buf); i++, j++)
            buf_min[j] = buf[i];

        p->condition.car_new.guar = atoi(buf_min);
        ident_buf(buf_min);
    }

    return EXIT_SUCCESS;
}

/*!@brief Меню*/
int menu(car *p, car *p_not, car_sort *s, car_sort *o, int *len_struct){
    int item, price_min, price_max;
    long long count = 0;
    long long time_sort_bubble = 0, time_sort_quick = 0;
    // Флаг выхода
    int flag_end = 1;

    clock_t now = 0, end = 0, now1 = 0, end1 = 0;
    clock_t now2 = 0, end2 = 0, now3 = 0, end3 = 0;

    while(flag_end)
    {
        printf("\n1: List of cars:\n"); //Вывод списка машин
        printf("2: Result\n"); // Вывод списка новых машин
        printf("3: Add a note\n"); // append
        printf("4: Sort record (key)\n"); // sort по ключам
        printf("5: Sort record\n"); // sort по ключам
        printf("6: Delete record\n"); // del
        printf("EXIT ? Input 0: \n"); //выход
        printf("\nSelect item:  ");

        car_hb(s, o, *len_struct);

        car_dont_hb(p, p_not, *len_struct);

        car_sort_init_frst(s, o, *len_struct);

        if (scanf("%d", &item) != 1 || item < 0 || item > MENU_LEN) {
            puts("\nERROR");
            return EXIT_FAILURE;
        }

        if (item == 1)
            print_struct(p, *len_struct);

        else if (item == 2) {
        /*
            printf("\nEnter price range (min / max): ");
            if (scanf("%d %d", &price_min, &price_max) != 2 || price_max < 0
                || price_min < 0 || price_min > price_max) {
                puts("\nERROR");
                return EXIT_FAILURE;
            }
        */
        print_result(now1, end1, now, end, now3, end3, now2, end2);
        }

        else if (item == 3)
        {
            append_struct(p, s, len_struct);
        }
        else if (item == 4)
        {
            count = 0;
            printf("\nRun sort");
            printf("\n Bubble sort\n DONT SORT\n");
            //Не отсортированная таблица ключей
            printf_result_sort(p, s, *len_struct);

            now = clock();
            while(count != AMOUNT_SORT) {
                sort_struct_bubble(s, *len_struct);
                count++;
                if (count != AMOUNT_SORT)
                    car_sort_init_frst(s, o, *len_struct);

            }
            end = clock();

            count = 0;

            printf("\nSORT\n");
            //отсортированная таблица ключей
            printf_result_sort(p, s, *len_struct);

            car_sort_init_frst(s, o, *len_struct); // Возвращение исходных значений

            printf("\n Shell sort\n DONT SORT\n");
            // не отсортированная таблица ключей
            printf_result_sort(p ,s, *len_struct);

            now1 = clock();

            while(count != AMOUNT_SORT) {
                sort_struct_quick(s, *len_struct);
                count++;
                if (count != AMOUNT_SORT)
                    car_sort_init_frst(s, o, *len_struct);

            }
            end1 = clock();

            printf("\nSORT\n");
            printf_result_sort(p, s, *len_struct);

            printf("\n");
            print_struct_sort(p, s, *len_struct);
            printf("\n\nTime bubble sort %lf\nTime Shell sort  %lf\n", (double) (end - now) / CLOCKS_PER_SEC, (double) (end1 - now1) / CLOCKS_PER_SEC);
            car_sort_init_frst(s, o, *len_struct);
        }
        else if (item == 5)
        {
            printf("\nShell sort\n");

            count = 0;

            now3 = clock();
            while (count != AMOUNT_SORT)
            {
                sort_dont_key_quick(p, *len_struct);
                count++;
                if (count != AMOUNT_SORT)
                    car_dont_hb(p_not, p, *len_struct);
            }
            end3 = clock();

            print_struct(p, *len_struct);

            car_dont_hb(p_not, p, *len_struct);

            count = 0;
            printf("\nBubble sort\n");

            now2 = clock();
            while (count != AMOUNT_SORT)
            {
                sort_dont_key_bubble(p, *len_struct);
                count++;
                if (count != AMOUNT_SORT)
                    car_dont_hb(p_not, p, *len_struct);
            }
            end2 = clock();

            print_struct(p, *len_struct);

            car_dont_hb(p_not, p, *len_struct);

            printf("\n\nTime bubble sort %lf\nTime Shell sort %lf\n", (double) (end2 - now2) / CLOCKS_PER_SEC, (double) (end3 - now3) / CLOCKS_PER_SEC);

        }
        else if (item == 6)
        {
            printf("\nRun delete record\n");
            del_struct_record(p, len_struct);
        }
        else if(item == 0)
            flag_end = 0;
    }

    return EXIT_SUCCESS;
}

int main() {

    car frst[STRUCT_LEN];
    car frst_n_key[STRUCT_LEN];
    car_sort frst_not_sort[STRUCT_LEN];
    car_sort frst_id[STRUCT_LEN];

    //счетчик реальная длина структуры
    int count = 0;
    // Буфер
    BUFER buf;
    //File
    FILE *PriceList;
    //Time for sort

    if ((PriceList = fopen("C:\\Users\\user\\CLionProjects\\TISD\\lab_02\\PriceList.txt", "r")) == NULL)
    {
        printf("FILE IS DEAD");
        return EXIT_FAILURE;
    }
    else
        printf("OPEN FILE\n");


    for (int i = 0; i < STRUCT_LEN; i++)
        ident_struct(&frst[i]);

    while (fgets(buf, BUF_LEN, PriceList) != NULL)
    {
        parser(&frst[count], &frst_id[count], buf);
        frst_id[count].id = count;
        ident_buf(buf);
        count++;
    }

    fclose(PriceList);

    car_hb(frst_id, frst_not_sort, count);

    car_dont_hb(frst, frst_n_key, count);

    menu(frst, frst_n_key, frst_id, frst_not_sort, &count);


    return EXIT_SUCCESS;
}