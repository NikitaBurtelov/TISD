#include "headers/what.h"
#include "headers/output.h"

typedef char BUFER[BUF_LEN];

//init bufer
int init_bufer(BUFER buf, int len)
{
    for (int i = 0; i < BUF_LEN - 1; i++)
        buf[i] = '\0';

    for (int i = 0; i < len; i++)
        if (scanf("%c", &buf[i]) != 1)
            return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

//Инициализация массива
int init_mass(Mass_double *p, Mass_int *s, int type_m)
{
    if (type_m == 0)
    {
        for (int i = 0; i < NMAX; i++)
            p->elem[i] = 0;
    }
    else
    {
        for (int i = 0; i < NMAX; i++)
            s->elem[i] = 0;
    }

    p->top = 0;
    s->top = 0;

    return EXIT_SUCCESS;
}

//Инициализация списка
int init_list(List_doubel *p, List_int *s, int type_l)
{
    if (type_l == 0)
    {
        for (int i = 0; i < NMAX; i++)
        {
            p->value = 0;
            p->next = 0;
        }
    }
    return EXIT_SUCCESS;
}

//Заполнение struct
int init_struct_mass(BUFER *buf, Mass_double *frst_md, Mass_int *frst_mi, int type_m, int len)
{
    if (type_m == 0)
    {
        for (int i = 0; i < len; i++)
        {
            if (scanf("%lf", &frst_md->elem[i]) != 1 && NMAX < frst_md->top)
                return EXIT_FAILURE;
            else
                frst_md->top++;
        }
    }
    else
    {
        for (int i = 0; i < len; i++)
        {
            if (scanf("%d", &frst_mi->elem[i]) != 1 && NMAX < frst_mi->top)
                return EXIT_FAILURE;
            else
                frst_mi->top++;
        }
    }

    frst_md->top--;
    frst_mi->top--;

    for (int i = 0; i < len; i++)
        printf("%d ", frst_mi->elem[i]);


    return EXIT_SUCCESS;
}

int app_struct_mass(Mass_double *frst_md, Mass_int *frst_mi, int type_m)
{
    if (type_m == 0)
    {
        if (scanf("%lf", &frst_md->elem[frst_md->top + 1]) != 1 && NMAX < frst_md->top)
            return EXIT_FAILURE;
        frst_md->top++;
    }
    else
    {
        if (scanf("%d", &frst_mi->elem[frst_mi->top + 1]) != 1 && NMAX < frst_mi->top)
            return EXIT_FAILURE;
        frst_mi->top++;
    }
    return EXIT_SUCCESS;
}

int del_struct_mass(Mass_double *frst_md, Mass_int *frst_mi, int type_m)
{
    if (type_m == 0)
    {
        if (frst_md->top != 0)
            frst_md->top--;
    }
    else
    {
        if (frst_mi->top != 0)
            frst_mi->top--;
    }

    return EXIT_SUCCESS;
}

int del_struct_list_int(List_int **head)
{
    if ((*head) == NULL)
        return EXIT_FAILURE;

    *head = (*head)->next;

    return EXIT_SUCCESS;
}

int del_struct_list_double(List_doubel **head)
{
    if ((*head) == NULL)
        return EXIT_FAILURE;

    *head = (*head)->next;

    return EXIT_SUCCESS;
}

int push_li(List_int **head)
{
    List_int *tmp = malloc(sizeof(List_int));

    if (tmp == NULL)
    {
        return EXIT_FAILURE;
    }
    tmp->next = *head;
    if (scanf("%d", &tmp->value) != 1)
        return EXIT_FAILURE;
    *head = tmp;

    return EXIT_SUCCESS;
}

int push_ld(List_doubel **head)
{
    List_doubel *tmp = malloc(sizeof(List_doubel));

    if (tmp == NULL)
    {
        return EXIT_FAILURE;
    }
    tmp->next = *head;
    if (scanf("%lf", &tmp->value) != 1)
        return EXIT_FAILURE;
    *head = tmp;

    return EXIT_SUCCESS;
}

void status_list_int(List_int **head)
{
    printf("\nTop Element Value: %d\n", (*head)->value);

}

int Menu(BUFER *buf, List_doubel *frst_ld, List_int *frst_li, Mass_double *frst_md, Mass_int *frst_mi)
{
    short flag = 1, menu_type = 0, menu_method = 0, menu_sec = 0; //1 - true
    int len = 0;

    while (flag)
    {
        printf("\n1. Select type\n");
        printf("0.EXIT\n");

        //Проверка на ввод
        if (scanf("%hi", &menu_type) != 1)
            return EXIT_FAILURE;
        //Определение типа
        if (menu_type == 1)
            printf("1. int\n2. double\n");// menu_type == 1 (int),  == 2 (double)
        else if(menu_type == 0)
        {
            flag = 0;
            return EXIT_SUCCESS;
        }
        //Проверка на ввод
        if (scanf("%hi", &menu_type) != 1) //menu_type - на выходе тип данных
            return EXIT_FAILURE;


        printf("2. Choose an implementation method\n");
        printf("0.EXIT\n");

        if (scanf("%hi", &menu_method) != 1)
            return EXIT_FAILURE;

        if (menu_method == 0)
        {
            flag = 0;
            return EXIT_SUCCESS;
        }
        else if (menu_method == 2)
        {
            printf("\n1. List\n2. Massiv\n");
            if (scanf("%hi", &menu_method) != 1) // menu_method == 1 (List) == 2 (Massiv)
                return EXIT_FAILURE;
        }

        printf("\nInput Len\n");

        if (scanf("%d", &len) != 1)
            return EXIT_FAILURE;

        printf("Input number:\n");
        // Init // menu_type == 1 (int),  == 2 (double) menu_method == 1 (List) == 2 (Massiv)
        if (menu_type == 1) //int
        {
            if (menu_method == 1)
                for (int i = 0; i < len; i++)
                    push_li(&frst_li);
            else
            {
                init_mass(frst_md, frst_mi, 1);
                init_struct_mass(buf, frst_md, frst_mi, 1, len);
            }
        }
        else //double
            if (menu_method == 1)
            {
                for (int i = 0; i < len; i++)
                    push_ld(&frst_ld);
            }
            else
            {
                init_mass(frst_md, frst_mi, 0);
                init_struct_mass(buf, frst_md, frst_mi, 0, len);
            }
        flag = 0;
    }

    flag = 1;

    while (flag) {
        printf("\nSelect menu item\n");
        printf("1. Print\n");
        printf("2. Delete\n");
        printf("3. Append\n");
        printf("4. Status\n");
        printf("0. Exit\n");

        if (scanf("%hi", &menu_sec) != 1)
            return EXIT_FAILURE;

        if (menu_sec == 0)
        {
            flag = 0;
            return EXIT_SUCCESS;
        }
        else if (menu_sec == 1)
        {
            if (menu_method == 2 && menu_type == 2)
                print_struct_mass(*frst_md, *frst_mi, 0);
            else if (menu_method == 2 && menu_type == 1)
                print_struct_mass(*frst_md, *frst_mi, 1);
            else if (menu_method == 1 && menu_type == 1)
                print_struct_list_int(frst_li);
        }
        else if (menu_sec == 2)
        {
            if (menu_method == 2 && menu_type == 2)
                del_struct_mass(frst_md, frst_mi, 0);
            else if (menu_method == 2 && menu_type == 1)
                del_struct_mass(frst_md, frst_mi, 1);
            else if (menu_method == 1 && menu_type == 2)
                del_struct_list_double(&frst_ld);
            else if (menu_method == 1 && menu_type == 1)
                del_struct_list_int(&frst_li);
        }
        else if (menu_sec == 3)
        {
            if (menu_method == 2 && menu_type == 2)
            {
                if (app_struct_mass(frst_md, frst_mi, 0) == EXIT_FAILURE)
                    return EXIT_FAILURE;
            }
            else if (menu_method == 2 && menu_type == 1)
            {
                if (app_struct_mass(frst_md, frst_mi, 1) == EXIT_FAILURE)
                    return EXIT_FAILURE;
            }
            else if (menu_method == 1 && menu_type == 2)
            {
                if (push_ld(&frst_ld) == EXIT_FAILURE)
                    return EXIT_FAILURE;
            }
            else if (menu_method == 1 && menu_type == 1)
            {
                if (push_li(&frst_li) == EXIT_FAILURE)
                    return EXIT_FAILURE;
            }

        }
    }

    return EXIT_SUCCESS;
}

int main()
{
    BUFER buf;
    List_int *frst_li = NULL;
    List_doubel *frst_ld = NULL;
    Mass_int frst_mi;
    Mass_double frst_md;


    if (Menu(&buf, frst_ld, frst_li, &frst_md, &frst_mi) == EXIT_FAILURE)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}