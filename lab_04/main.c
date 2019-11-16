#include "headers/what.h"
#include "headers/output.h"
#include "headers/maze.h"

typedef char BUFER[BUF_LEN];

//Инициализация массива
int init_mass(Mass_double *p, Mass_int *s, int type_m)
{
    if (type_m == 0)
    {
        for (int i = 0; i < NMAX; i++)
            p->elem[i] = 0;
    }
    else if (type_m == 1)
    {
        for (int i = 0; i < NMAX; i++)
            s->elem[i] = 0;
    }

    p->top = 0;
    s->top = 0;

    return EXIT_SUCCESS;
}

int chek_mass_number(Mass_str *s, List_str *head, int len, int type_struct)
{
    short flag = 0; //0 - выражения нет, 1 - выражение есть
    char str;
    for (int i = 0; i < len; i++)
    {
        if (type_struct == 0)
            str = s->elem[i];
        else
            str = head->value;

        if (str == '+' || str == '-' || str == '*' || str == '/')
        {
            flag = 1;
            break;
        }
        if (type_struct == 1)
            if (head->next != NULL)
                head = head->next;
    }

    return flag;
}

int chek_struct_mass_str(Mass_str *s, List_str *p, int len, int type_d)
{
    // l -left, r - right, br - скобка, fbr - фигурная скобка, sbr - квадратная скобка
    int l_br = 0, r_br = 0, l_fbr = 0, r_fbr = 0, l_sbr = 0, r_sbr = 0;
    char param = '\0';

    if (chek_mass_number(s, p, len, type_d) == 1)
    {
        for (int i = 0; i < len; i++)
        {
            if (type_d == 0)
                param = s->elem[i];
            else if (type_d == 1 && p != NULL)
            {
                param = p->value;
                p = p->next;
            }

            if (param == '(')
                l_br++;

            if (param == ')')
                r_br++;

            if (param == '{')
                l_fbr++;

            if (param == '}')
                r_fbr++;

            if (param == '[')
                l_sbr++;

            if (param == ']')
                r_sbr++;
        }

        if (l_br == r_br && l_fbr == r_fbr && l_sbr == r_sbr)
            printf("\nBrackets are partially true\n");
        else
            printf("\nBrackets are not partially\n");
    }
    else
        printf("\nYou have entered not an expression\n");

    return EXIT_SUCCESS;
}

int init_mass_str(Mass_str *s, int len)
{
    for (int i = 0; i < NMAX; i++)
    {
        s->elem[i] = '\0';
    }

    s->top = 0;

    for (int i = 0; i <= len; i++)
    {
        if (scanf("%c", &s->elem[i]) != 1 && NMAX < s->top)
            return EXIT_FAILURE;
        else
            s->top++;
    }

    for (int i = 0; i < len; i++)
    {
        s->elem[i] = s->elem[i+1];
    }

    s->top--;

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
int init_struct_mass(Mass_double *frst_md, Mass_int *frst_mi, int type_m, int len)
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

int init_struct_mass_str(Mass_str *frst_ms, int len)
{
    for (int i = 0; i <= len; i++)
    {
        if (scanf("%c", &frst_ms->elem[i]) != 1 && NMAX < frst_ms->top)
            return EXIT_FAILURE;
        else
            frst_ms->top++;
    }

    frst_ms->top--;

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

int app_struct_mass_str(Mass_str *frst_ms)
{
    printf("Input symbol: ");

    if (scanf("%s", &frst_ms->elem[frst_ms->top + 1]) != 1 && NMAX < frst_ms->top)
        return EXIT_FAILURE;
    frst_ms->top++;

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

int del_struct_mass_str(Mass_str *frst_ms)
{
    if (frst_ms->top != 0)
        frst_ms->top--;

    return EXIT_SUCCESS;
}

int del_struct_list_int(List_int **head)
{
    List_int *point = NULL;

    if ((*head) == NULL)
        return EXIT_FAILURE;
    point = *head;
    *head = (*head)->next;
    free(point);

    return EXIT_SUCCESS;
}

int del_struct_list_double(List_doubel **head)
{
    List_doubel *point = NULL;

    if ((*head) == NULL)
        return EXIT_FAILURE;
    point = *head;
    *head = (*head)->next;
    free(point);

    return EXIT_SUCCESS;
}

int del_struct_list_str(List_str **head)
{
    List_str *point = NULL;

    if ((*head) == NULL)
        return EXIT_FAILURE;
    point = *head;
    *head = (*head)->next;
    free(point);

    return EXIT_SUCCESS;
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

int push_ls(List_str **head, int flag)
{
    List_str *tmp = malloc(sizeof(List_str));

    if (tmp == NULL)
    {
        return EXIT_FAILURE;
    }
    tmp->next = *head;
    if (flag)
    {
        if (scanf("%c", &tmp->value) != 1)
            return EXIT_FAILURE;
    }
    else
    {
        if (scanf("%s", &tmp->value) != 1)
            return EXIT_FAILURE;
    }
    *head = tmp;

    return EXIT_SUCCESS;
}

void status_list_int(List_int *head, int len)
{
    printf("\nTop Element Value: %d\n", head->value);
    printf("Stack length: %d\n", len);
}

void status_list_str(List_str *head, int len)
{
    printf("\nTop Element Value: %c\n", head->value);
    printf("Stack length: %d\n", len);
}

void status_list_double(List_doubel *head, int len)
{
    printf("\nTop Element Value: %lf\n", head->value);
    printf("Stack length: %d\n", len);
}

void status_mass_int(Mass_int *frst_mi, int len)
{
    printf("\nTop Element Value: %d\n", frst_mi->elem[len - 1]);
    printf("Stack length: %d\n", len);
}

void status_mass_str(Mass_str *frst_ms, int len)
{
    printf("\nTop Element Value: %c\n", frst_ms->elem[len - 1]);
    printf("Stack length: %d\n", len);
}

void status_mass_double(Mass_double *frst_md, int len)
{
    printf("\nTop Element Value: %lf\n", frst_md->elem[len - 1]);
    printf("Stack length: %d\n", len);
}

int Menu(List_doubel *frst_ld, List_int *frst_li, List_str *frst_ls, Mass_double *frst_md, Mass_int *frst_mi, Mass_str *frst_ms)
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
        if (menu_type == 6) //пасхалка
            break;
        //Определение типа
        if (menu_type == 1)
            printf("1. int\n2. double\n3. String\n");// menu_type == 1 (int),  == 2 (double)
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

        if (menu_type == 3 && menu_method == 1)
            len++;

        printf("Input number:\n");
        // Init // menu_type == 1 (int),  == 2 (double) menu_method == 1 (List) == 2 (Massiv)
        if (menu_type == 1) //int
        {
            if (menu_method == 1)
                for (int i = 0; i < len; i++)
                    push_li(&frst_li);
            else if (menu_method == 2)
            {
                init_mass(frst_md, frst_mi, 1);
                init_struct_mass(frst_md, frst_mi, 1, len);
            }
        }
        else if (menu_type == 2)//double
        {
            if (menu_method == 1)
            {
                for (int i = 0; i < len; i++)
                    push_ld(&frst_ld);
            }
            else if (menu_method == 2)
            {
                init_mass(frst_md, frst_mi, 0);
                init_struct_mass(frst_md, frst_mi, 0, len);
            }

        }
        else if (menu_type == 3)
        {
            if (menu_method == 2)
                init_mass_str(frst_ms, len);

            else if (menu_method == 1)
            {
                for (int i = 0; i < len; i++)
                    push_ls(&frst_ls, 1);
            }
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
        printf("5. Check brackets\n");
        printf("6. Labyrinth\n");
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
            else if (menu_method == 2 && menu_type == 3)
                print_struct_mass_str(*frst_ms);
            else if (menu_method == 1 && menu_type == 1)
                print_struct_list_int(frst_li);
            else if (menu_method == 1 && menu_type == 2)
                print_struct_list_int(frst_li); // Поменять на double
            else if (menu_method == 1 && menu_type == 3)
                print_struct_list_str(frst_ls);
        }
        else if (menu_sec == 2)
        {
            if (menu_method == 2 && menu_type == 2)
                del_struct_mass(frst_md, frst_mi, 0);
            else if (menu_method == 2 && menu_type == 1)
                del_struct_mass(frst_md, frst_mi, 1);
            else if (menu_method == 2 && menu_type == 3)
                del_struct_mass_str(frst_ms);
            else if (menu_method == 1 && menu_type == 2)
            {
                del_struct_list_double(&frst_ld);
            }
            else if (menu_method == 1 && menu_type == 1)
            {
                del_struct_list_int(&frst_li);
            }
            else if (menu_method == 1 && menu_type == 3)
            {
                del_struct_list_str(&frst_ls);
            }
            len--;
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
            else if (menu_method == 2 && menu_type == 3)
            {
                if (app_struct_mass_str(frst_ms) == EXIT_FAILURE)
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
            else if (menu_method == 1 && menu_type == 3)
            {
                if (push_ls(&frst_ls, 0) == EXIT_FAILURE)
                    return EXIT_FAILURE;
            }
            len++;
        }
        else if (menu_sec == 4)
        {
            if (menu_method == 1 && menu_type == 1)
                status_list_int(frst_li, len);

            else if (menu_method == 1 && menu_type == 2)
                status_list_double(frst_ld, len);

            else if (menu_method == 1 && menu_type == 3)
                status_list_str(frst_ls, len);

            else if (menu_method == 2 && menu_type == 1)
                status_mass_int(frst_mi, len);

            else if (menu_method == 2 && menu_type == 2)
                status_mass_double(frst_md, len);

            else if (menu_method == 2 && menu_type == 3)
                status_mass_str(frst_ms, len);
        }
        else if (menu_sec == 5 && menu_type == 3)
        {
            if (menu_method == 1)//list
                chek_struct_mass_str(frst_ms, frst_ls, len, 1);
            else if (menu_method == 2)//mass
                chek_struct_mass_str(frst_ms, frst_ls, len, 0);

        }
        else if (menu_sec == 6)
            movement();
    }

    return EXIT_SUCCESS;
}

int main()
{
    List_int *frst_li = NULL;
    List_doubel *frst_ld = NULL;
    List_str *frst_ls = NULL;
    Mass_int frst_mi;
    Mass_double frst_md;
    Mass_str frst_ms;

    if (Menu(frst_ld, frst_li, frst_ls, &frst_md, &frst_mi, &frst_ms) == EXIT_FAILURE)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}