#include "includes/table_routines.h"
#include "includes/idents.h"
#include "includes/sorts.h"

// Строка bufer
// указатель на переменнную типа car
int strprs(str bufer, car *new_car)
{
    str num;
    str str2;
    int flag;
    ident_bufer(num);
    ident_car(new_car);
    if(sscanf(bufer, "%[^,],%[^,],%d,%[^,],%d", str2, str2, &flag, str2, &new_car->cond_flag) != 5)
    {
        printf("Can not read file!\n");
        return EXIT_FAILURE;
    }
    if(new_car->cond_flag == 0)
    {
        if(sscanf(bufer,"%[^,],%[^,],%d,%[^,],%d,%d", new_car->model, new_car->country, &new_car->price,
              new_car->colour, &new_car->cond_flag, &new_car->condition.new_s.guarantee) != 6)
            {
                printf("Can not read file!\n");
                return EXIT_FAILURE;
            }
    }
    else
    {
        if(sscanf(bufer,"%[^,],%[^,],%d,%[^,],%d,%d,%ld,%d,%d", new_car->model, new_car->country, &new_car->price,
              new_car->colour, &new_car->cond_flag, &new_car->condition.used_s.year,
              &new_car->condition.used_s.run, &new_car->condition.used_s.repairs, &new_car->condition.used_s.users) != 9)
            {
                printf("Can not read file!\n");
                return EXIT_FAILURE;
            }
    }
    new_car->empt = 1;
    return EXIT_SUCCESS;
}
// Парсит строку bufer и заполняет поля объекта new_car типа car

// Значение переменной типа car
void print_elem(car my_car)
{
    if(my_car.empt == 1)
    {
        if (my_car.cond_flag == 0)
            printf("│%3d|%20s|%10s|%5d|%10s|%9d|   %7d|    -    |       -      |   -   |   -   │\n", my_car.id, my_car.model, my_car.country, my_car.price, my_car.colour, my_car.cond_flag, my_car.condition.new_s.guarantee);
        else
            printf("│%3d|%20s|%10s|%5d|%10s|%9d|     -    |%9ld|%14d|%7d|%7d│\n", my_car.id, my_car.model, my_car.country, my_car.price, my_car.colour, my_car.cond_flag,
                   my_car.condition.used_s.run, my_car.condition.used_s.year, my_car.condition.used_s.users, my_car.condition.used_s.repairs);
    }
}
// Выводит значение полей объекта my_car типа car

// Указатель на массив переменных типа car
void print_cars(car *list)
{
    int i = 0;
    printf("┌───┬────────────────────┬──────────┬─────┬──────────┬─────────┬──────────┬─────────┬──────────────┬───────┬───────┐\n");
    printf("│%3s│%20s│%10s│%5s│%10s│%9s│ %7s│ %5s│ %3s│ %3s│%s│\n","ID", "Model","Country", "Price", "Colour", "Condition", "Guarantee", "     Run", "Year of build", "Owners", "Repairs");
    printf("├───┼────────────────────┼──────────┼─────┼──────────┼─────────┼──────────┼─────────┼──────────────┼───────┼───────┤\n");
    while(list[i].empt == 1)
    {
        print_elem(list[i]);
        i++;
    }
    printf("└───┴────────────────────┴──────────┴─────┴──────────┴─────────┴──────────┴─────────┴──────────────┴───────┴───────┘\n");
}
// Выводит массив list значений объектов car

// Указатель на массив переменных типа car
int add_rec(car *list, flags *flag, int *len)
{
    if (*len == LISTLEN)
    {
        printf("There are no free fields in data base!\n");
        return EXIT_FAILURE;
    }
    int i = *len;
    ident_car(&list[i]);

    printf("Input car's model:");
    scanf("%[^\n]", list[i].model);
    if(strlen(list[i].model) == 0)
    {
        printf("Wrong input!\n");
        return EXIT_FAILURE;
    }

    printf("Input car's country of build:");
    clear();
    scanf("%[^\n]", list[i].country);
    if(strlen(list[i].model) == 0)
    {
        printf("Wrong input!\n");
        return EXIT_FAILURE;
    }

    printf("Input car's price:");
    clear();
    if(scanf("%d", &list[i].price) != 1)
    {
        printf("Wrong input!\n");
        ident_car(&list[i]);
        return EXIT_FAILURE;
    }

    printf("Input car's colour:");
    clear();
    scanf("%[^\n]", list[i].colour);
    if(strlen(list[i].model) == 0)
    {
        printf("Wrong input!\n");
        return EXIT_FAILURE;
    }

    printf("Input car's condition(0-new/1-used):");
    clear();
    if(scanf("%d", &list[i].cond_flag) != 1)
    {
        printf("Wrong input!\n");
        ident_car(&list[i]);
        return EXIT_FAILURE;
    }
    if(list[i].cond_flag != 0 && list[i].cond_flag != 1)
    {
        printf("Wrong input!\n");
        ident_car(&list[i]);
        return EXIT_FAILURE;
    }

    if (list->cond_flag == 0)
    {
        printf("Input duration of car's guarantee(in years):");
        clear();
        if(scanf("%d", &list[i].condition.new_s.guarantee) != 1)
        {
            printf("Wrong input!\n");
            ident_car(&list[i]);
            return EXIT_FAILURE;
        }
    }
    else
    {
        printf("Input car's year of build:");
        clear();
        if(scanf("%d", &list[i].condition.used_s.year) != 1)
        {
            printf("Wrong input!\n");
            ident_car(&list[i]);
            return EXIT_FAILURE;
        }
        printf("Input car run:");
        clear();
        if(scanf("%ld", &list[i].condition.used_s.run) != 1)
        {
            printf("Wrong input!\n");
            ident_car(&list[i]);
            return EXIT_FAILURE;
        }
        printf("Input number of car repairs:");
        clear();
        if(scanf("%d", &list[i].condition.used_s.users) != 1)
        {
            printf("Wrong input!\n");
            ident_car(&list[i]);
            return EXIT_FAILURE;
        }

        printf("Input number of car owners:");
        clear();
        if(scanf("%d", &list[i].condition.used_s.repairs) != 1)
        {
            printf("Wrong input!\n");
            ident_car(&list[i]);
            return EXIT_FAILURE;
        }
    }

    int k = 0;
    for(; k < *len; k++)
    {
        for(int j = 0; j < *len; j++)
        {
            if(list[j].id == k)
                break;
            else if(j == *len)
            {
                list[i].id = k;
            }
        }
        if(list[i].id != 0)
            break;
    }

    if(list[i].id == 0)
        list[i].id = k;

    list[i].empt = 1;
    *len += 1;
    flag->car_flag = 0;

    return EXIT_SUCCESS;
}
// Добавляет в свободный элемент массива new_car объект car;
// Значений полей вводятся с клавиатуры
// Меняет значение base_flag на 1(применены изменения в базе)

// Указатель на переменную типа int
int choose_feild(int *field)
{
    printf("Choose field:"
           "2 - Model; 3 - Country; 4 - price; 5 - Colour; 6 - condition\n"
           "(only for new cars) 7 - Guarantee\n"
           "(only for used cars) 8 - Year; 9 - Run; 10 - Number of repairs; 11 - Number of owners\n"
           "Input: \n");
    if(scanf("%d", field) != 1)
    {
        printf("Wrong input!\n");
        return EXIT_FAILURE;
    }
    if(*field > 11 || *field < 2)
    {
        printf("Wrong input!\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
// Выбирает поле с которым хочет взаимодействовать пользователь
// Сохраняет значение в переменную field типа int

// Указатель на переменную типа int и указатель на переменную типа choose
int input_field_value(int field, choose *field_value)
{
    printf("Input field value: ");
    if (field == 2 || field == 3 || field == 5)
    { // Ввод строкового значения
        field_value->flag = 0;
        if(scanf(" %99[^\n]", field_value->value.buf) != 1)
        {
            printf("Wrong input!\n");
            return EXIT_FAILURE;
        }
        if(strlen(field_value->value.buf) == 0)
        {
            printf("Wrong input!\n");
            return EXIT_FAILURE;
        }

    }
    else
    { // Ввод целочисленного значения
        field_value->flag = 1;
        if(scanf("%ld", &field_value->value._int_) != 1)
        {
            printf("Wrong input!\n");
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}
// Вводит значения поля с которым взаимодействует пользователь
// Ввод с клавиатуры
// Сохраняет значение в переменную feild_value типа choose

// Значение переменной field типа int
// указатель на переменную my_car типа car
// значение переменной field_value типа choose
void delete_rec(int field, car *my_car, choose field_value)
{
    switch (field)
    {
    case 2: // удаление по модели
    {
        if(strcmp(my_car->model, field_value.value.buf) == 0)
        {
            ident_car(my_car);
        }
        break;
    }
    case 3: // удаление по стране
    {
        if(strcmp(my_car->country, field_value.value.buf) == 0)
            ident_car(my_car);
        break;
    }
    case 5: // удаление по цвету
    {
        if(strcmp(my_car->colour, field_value.value.buf) == 0)
            ident_car(my_car);
        break;
    }
    case 4: // удаление по цене
    {
        if(field_value.value._int_ == my_car->price)
            ident_car(my_car);
        break;
    }
    case 6: // удаление по состоянию
    {
        if(field_value.value._int_ == my_car->cond_flag)
            ident_car(my_car);
        break;
    }
    case 7: // удаление по гарантии
    {
        if(field_value.value._int_ == (int)my_car->condition.new_s.guarantee && my_car->cond_flag == 0)
            ident_car(my_car);
        break;
    }
    case 9: // удаление по пробегу
    {
        if(field_value.value._int_ == my_car->condition.used_s.run && my_car->cond_flag == 1)
            ident_car(my_car);
        break;
    }
    case 8: // удаление по году выпуска
    {
        if(field_value.value._int_ == my_car->condition.used_s.year && my_car->cond_flag == 1)
            ident_car(my_car);
        break;
    }
    case 10: // удаление по количеству ремонтов
    {
        if(field_value.value._int_ == my_car->condition.used_s.repairs && my_car->cond_flag == 1)
            ident_car(my_car);
        break;
    }
    case 11:  // удадение по количеству собственников
    {
        if(field_value.value._int_ == my_car->condition.used_s.users && my_car->cond_flag == 1)
            ident_car(my_car);
        break;
    }
    }
}
// Объявляет объект типа car недействительным,
// если значение поля field объекта car совпадает со значением объекта field_value типа choose

// Указатель на массив переменных типа car
int delete_procedure(key *key_list, car *car_list, int *car_list_len, int *key_list_len)
{
    choose field_value;
    int field;

    if(choose_feild(&field) == EXIT_FAILURE)
        return EXIT_FAILURE;
    if(input_field_value(field, &field_value) == EXIT_FAILURE)
        return EXIT_FAILURE;
    if(field == 6 && (field_value.value._int_ != 0 && field_value.value._int_ != 1))
    {
        printf("Wrong field value!\n");
        return EXIT_FAILURE;
    }

    for(int i = 0; i < LISTLEN; i++)
    {
        delete_rec(field, &car_list[i], field_value);
    }

    int i = 1;
    while(i < LISTLEN)
    {
        if(car_list[i-1].empt == 0)
        {
            for(int j = i - 1; j < LISTLEN; j++)
                save_car(&car_list[j+1], &car_list[j]);
            i--;
        }
        i++;
    }
    *car_list_len = i;
    *key_list_len = i;
    fill_keys(key_list, car_list, car_list_len, key_list_len);
    return EXIT_SUCCESS;
}
// Удаляет из массива car_list типа car все элеметы
// Которые имеют выбранное пользователем значение выбранного пользователем поля
// Выбор поля и ввод значения с клавиатуры
// Меняет значение base_flag на 1(применены изменения в базе)

//  Указатель на массив key_list типа key
//  Указатель на массив car_list типа car
//  Переменная len типа int
//  Указатель на переменную key_list_len типа int
void fill_keys(key *key_list, car *car_list, int *car_list_len, int *key_list_len)
{
    int j, i;
    // i - счетчик отвечающий за элементы в массиве car_list
    // j - счетчик отвечающий за элементы в массиве key_list_len
    for(i = 0, j = 0; j < LISTLEN; j++)
        if(car_list[j].empt == 1)
        {
            key_list[i].value = car_list[j].price;
            key_list[i].id = car_list[j].id;
            i++;
            *car_list_len = j + 1;
        }
        else
        {
            ident_car(&car_list[j]);
        }

    *key_list_len = i;
}
//  Заполняет массив key_list ключей значениями соответственно значениям массива car_list

//  Указатель на массив key_list типа key
//  Переменная key_list_len типа int
void print_keys(key *key_list, int key_list_len)
{
    printf("┌───┬────────┐\n");
    printf("│ ID│   Price│\n");
    printf("├───┼────────┤\n");

    for(int i = 0; i < key_list_len; i++)
    {
        printf("│%3d| %7d│\n", key_list[i].id, key_list[i].value);
    }
    printf("└───┴────────┘\n");
}
// Печатает массив key_list ключей

//  Указатель на массив key_list типа key
//  Указатель на массив car_list типа car
//  Переменная car_list_len типа int
//  Переменная key_list_len типа int
void print_table_by_keys(car *car_list, int car_list_len, key *key_list, int key_list_len)
{

    printf("┌───┬────────────────────┬──────────┬─────┬──────────┬─────────┬──────────┬─────────┬──────────────┬───────┬───────┐\n");
    printf("│%3s│%20s│%10s│%5s│%10s│%9s│ %7s│ %5s│ %3s│ %3s│%s│\n","ID", "Model","Country", "Price", "Colour", "Condition", "Guarantee", "     Run", "Year of build", "Owners", "Repairs");
    printf("├───┼────────────────────┼──────────┼─────┼──────────┼─────────┼──────────┼─────────┼──────────────┼───────┼───────┤\n");
    for(int i = 0; i < car_list_len; i++)
    {
        for(int j = 0; j < key_list_len; j++)
        {
            if(key_list[i].id == car_list[j].id)
            {
                print_elem(car_list[j]);
                break;
            }
        }
    }
    printf("└───┴────────────────────┴──────────┴─────┴──────────┴─────────┴──────────┴─────────┴──────────────┴───────┴───────┘\n");
}
// печатает массив car_list по упорядоченному массиву ключей key_list

// Очищение stdin (my_fflush)
void clear (void)
{
   fflush(stdin);
  if(!feof(stdin))
    while ( getchar() != '\n' );
}

// находит все машины по полю "марка" в отрезке цен [min; max] у которых 0 ремонтов и 1 владелец
int search_rec(car *car_list, int car_list_len, flags *flag)
{
    if(flag->base_flag == 0 || car_list_len == 0)
    {
        printf("Empty base, you have nothing to search!\n");
        return EXIT_FAILURE;
    }

    str model;
    int min = 0, max = 0, pr = 0;
    printf("Input model: ");
    fgets(model, STRLEN, stdin);
    if(strlen(model) == 1)
    {
        printf("Wrong input!\n");
        return EXIT_FAILURE;
    }
    int a = (int)-strlen(model) - 1;
    model[a] = 0;
    printf("Input min and max price: ");
    if(scanf("%d %d", &min, &max) != 2 || min > max || min <= 0 || max <= 0)
    {
        printf("Wrong input!\n");
        return EXIT_FAILURE;
    }

    for(int i = 0; i < car_list_len; i++)
        if(strcmp(car_list[i].model, model) == 0)
            if(car_list[i].cond_flag == 1 && car_list[i].price <= max && car_list[i].price >= min)
                if(car_list[i].condition.used_s.users == 1 && car_list[i].condition.used_s.repairs == 0)
                {
                    pr++;
                    if(pr == 1)
                    {
                        printf("┌───┬────────────────────┬──────────┬─────┬──────────┬─────────┬──────────┬─────────┬──────────────┬───────┬───────┐\n");
                        printf("│%3s│%20s│%10s│%5s│%10s│%9s│ %7s│ %5s│ %3s│ %3s│%s│\n","ID", "Model","Country", "Price", "Colour", "Condition", "Guarantee", "     Run", "Year of build", "Owners", "Repairs");
                        printf("├───┼────────────────────┼──────────┼─────┼──────────┼─────────┼──────────┼─────────┼──────────────┼───────┼───────┤\n");
                    }
                    print_elem(car_list[i]);
                }

    if(!pr)
        printf("There are no records satysfying the filter!\n");
    else
        printf("└───┴────────────────────┴──────────┴─────┴──────────┴─────────┴──────────┴─────────┴──────────────┴───────┴───────┘\n");

    return EXIT_SUCCESS;
}
