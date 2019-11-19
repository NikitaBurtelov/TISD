#include "includes/file_routines.h"
#include "includes/table_routines.h"
#include "includes/idents.h"

// указатель на перeменную типа FILE
int my_fopen(FILE **fp, char *rc)
{
    str file_name;
    ident_bufer(file_name);
    FILE *tmp = NULL;
    char mode;

    printf("Do you want open existing file or create new?\n");

    printf("r - open existing file\n"
           "w - create new file\n"
           "b - abort operation and go back to menu\n");
    printf("Input:");
    scanf("%c", &mode);

    if(mode == 'b')
    {
        return EXIT_FAILURE;
    }
    else if(mode == 'r')
    {
        printf("Input file_name:");
        scanf("%s", file_name);
        tmp = fopen(file_name, "r");
        if(!tmp)
        {
            printf("File does not exist!\n");
            return EXIT_FAILURE;
        }
        *fp = tmp;
        printf("File successfully opened!\n");
    }
    else if(mode == 'w')
    {
        printf("Input file_name:");
        clear();
        scanf("%s", file_name);
        file_name[strlen(file_name)] = 0;
        tmp = fopen(file_name, "r");
        if(tmp)
        {
            printf("File exists, if you continue, current file data will be deleted. Continue?y/n : ");
            scanf("%c", &mode);
            clear();
            if(mode == 'n')
            {
                fclose(tmp);
                printf("Operation successfully aborted!\n");
                return EXIT_FAILURE;
            }
            else if (mode != 'y')
            {
                printf("Wrong input!\n");
                return EXIT_FAILURE;
            }
        }
        if ((mode == 'y' && tmp) || mode == 'w')
        {
            if(tmp)
                fclose(tmp);
            *fp = fopen(file_name, "w+r");
            if(!*fp)
            {
                printf("Error occurred during opening file!\n");
                return EXIT_FAILURE;
            }
            printf("File successfully opened!\n");
            *rc = 'w';
        }
    }
    else
    {
        printf("Wrong mode!\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
// Открывает файл "file_name" в переменню fp

// указатель на переменную типа FILE
// строку bufer
int read_rec(FILE *fp, str bufer)
{
    int tmp;
    if (!feof(fp))
    {
        ident_bufer(bufer);
        fgets(bufer, STRLEN, fp);
        if(strlen(bufer) == 0)
            return EOF;
        tmp = (int)strlen(bufer) - 1;
        bufer[tmp] = 0;
        return EXIT_SUCCESS;
    }
    return EOF;
}
// читает строку из файла fp в строку bufer

// указатель типа FILE
// массив переменных типа car
// указатель на переменную типа int
int read_file(FILE *fp, car *car_list, int *len)
{
    str bufer;
    int i = 0;

    while(read_rec(fp, bufer) == EXIT_SUCCESS)
    {
        if(strprs(bufer, &car_list[i]) == EXIT_FAILURE)
            return EXIT_FAILURE;
        i++;
        car_list[i].id = i;
    }
    *len = i;
    if(*len == 0)
    {
        printf("File is empty!\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
// читает файл и заполняет объекты массива car_list
// когда заканчивается файл неявно возвращает количество действительных элементов
// находящихся в массиве car_list

// указатель на переменную fp типа FILE
// указатель на массив list типа car
// переменная len типа int
int my_fwrite(FILE *fp, car *list, int len)
{
    for(int i = 0; i < len; i++)
        if(list[i].cond_flag == 0)
            fprintf(fp, "%s,%s,%d,%s,%d,%d\n", list[i].model, list[i].country, list[i].price,
                    list[i].colour, list[i].cond_flag, list[i].condition.new_s.guarantee);
        else
            fprintf(fp, "%s,%s,%d,%s,%d,%d,%ld,%d,%d\n", list[i].model, list[i].country, list[i].price,
                    list[i].colour, list[i].cond_flag, list[i].condition.used_s.year, list[i].condition.used_s.run,
                    list[i].condition.used_s.repairs, list[i].condition.used_s.users);
    return EXIT_SUCCESS;
}
// записывает в файл fp, массив записей list размером len
// соответственно условному расположению полей записи
// одна строка файла - одна запись

// двойной указатель на переменную fp типа FILE
// указатель на переменную base_flag типа int
// указатель на переменную file_name типа str
// указатель на массив list типа car
// переменная len типа int
int save_changes(car *list, int len, flags flag)
{
    if (flag.base_flag == 0 || len == 0)
    {
        printf("Empty base, you have nothing to save!\n");
        return EXIT_FAILURE;
    }
    FILE *fp = NULL;
    str file_name;
    ident_bufer(file_name);
    char mode;


    printf("Do you want to save changes?y/n : ");
    scanf("%c", &mode);
    clear();
    if(mode == 'n')
        return EXIT_FAILURE;
    else if(mode != 'y')
    {
        printf("Wrong input!\n");
        return EXIT_FAILURE;
    }


    printf("Do you want to save data in existing file or create new?\n");
    printf("r - save to existing file(file will be rewritten)\n"
           "w - create new file\n"
           "b - abort operation and go back to menu\n");
    printf("Input:");
    scanf("%c", &mode);

    FILE *tmp;
    if(mode == 'b')
        return EXIT_FAILURE;
    else if(mode == 'r')
        {
            printf("Input file_name:");
            clear();
            scanf("%s", file_name);
            tmp = fopen(file_name, "r");
            if(!tmp)
            {
                printf("File does not exist!\n");
                return EXIT_FAILURE;
            }
            fp = tmp;
        }
        else if(mode == 'w')
        {
            printf("Input file_name:");
            scanf("%s", file_name);
            file_name[strlen(file_name)] = 0;
            tmp = fopen(file_name, "r");
            if(tmp)
            {
                printf("File exists, if you continue, current file data will be deleted. Continue?y/n : ");
                clear();
                scanf("%c", &mode);
                clear();
                if(mode == 'n')
                {
                    fclose(tmp);
                    printf("Operation successfully aborted!\n");
                    return EXIT_FAILURE;
                }
                else if (mode != 'y')
                {
                    printf("Wrong input!\n");
                    return EXIT_FAILURE;
                }
            }
            else
            {
                fp = fopen(file_name, "w+r");
                if(!fp)
                {
                    printf("Error occurred during opening file!\n");
                    return EXIT_FAILURE;
                }
                printf("File successfully opened!\n");
            }
        }
    else
    {
        printf("Wrong input!\n");
        return EXIT_FAILURE;
    }

    printf("Do you want to save changes to %s?y/n : ", file_name);
    clear();
    scanf("%c", &mode);
    if(mode == 'y')
    {
        if(!tmp)
            fclose(fp);
        fp = fopen(file_name, "w");
        my_fwrite(fp, list, len);
        fclose(fp);
        printf("Changes successfully saved to %s\n", file_name);
    }
    else if(mode != 'n')
    {
        printf("Wrong input!\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
// Предлагает пользователю сохранить изменения в базе list длины len в открытый файл file_name
// если изменения были внесены(base_flag: 0 - не внесены 1 - внесены)
