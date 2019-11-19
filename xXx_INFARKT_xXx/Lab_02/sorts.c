#include "includes/sorts.h"
#include "includes/idents.h"

// указатель на переменную from типа key
// указатель на переменную to типа key
void save_key(key *from, key *to)
{
    to->value = from->value;
    to->id = from->id;
}
// сохраняет значения полей из from в to

// указатель на массив list типа key
// переменная х типа int
// переменная у типа int
void swap_key(key *list, int x, int y)
{
    key tmp;
    ident_key(&tmp);
    save_key(&list[x], &tmp);
    save_key(&list[y], &list[x]);
    save_key(&tmp, &list[y]);
}
// меняет местами значения полей list[x] и list[y]

// Переменная len типа int
// Указатель на массив list типа key
double shell_key_sort(int len, key *list)
{
    clock_t start, end;
    int i, j, step;
    key tmp;
    start = clock();
    for (step = len / 2; step > 0; step /= 2)
        for (i = step; i < len; i++)
        {
            save_key(&list[i], &tmp);
            for (j = i; j >= step; j -= step)
            {
                if (tmp.value < list[j - step].value)
                {
                    save_key(&list[j-step], &list[j]);
                }
                else
                    break;
            }
            save_key(&tmp, &list[j]);
        }
    end = clock();
    return ((double)(end - start))/CLOCKS_PER_SEC;
}
// сортирует массив list по полю value

// Переменная len типа int
// Указатель на массив list типа key
double buble_key_sort(int len, key *list)
{
    clock_t start, end;
    int i, j;
    start = clock();
    for (i = 0; i < len-1; i++)
        for (j = 0; j < len-i-1; j++)
            if (list[j].value > list[j+1].value)
                swap_key(list, j, j+1);
    end = clock();
    return ((double)(end - start))/CLOCKS_PER_SEC;
}
// сортирует массив list по полю value

// указатель на переменную хр типа car
// указатель на перемeнную ур типа car
void save_car(car *from, car *to)
{
    to->id = from->id;
    to->empt = from->empt;
    strcpy(to->model, from->model);
    to->price = from->price;
    strcpy(to->colour, from->colour);
    strcpy(to->country, from->country);
    to->cond_flag = from->cond_flag;
    if(to->cond_flag == 0)
    {
        to->condition.new_s.guarantee = from->condition.new_s.guarantee;
    }
    else
    {
        to->condition.used_s.run = from->condition.used_s.run;
        to->condition.used_s.year = from->condition.used_s.year;
        to->condition.used_s.users = from->condition.used_s.users;
        to->condition.used_s.repairs = from->condition.used_s.repairs;
    }
}
// сохраняет значения полей из from в to

// указатель на массив list типа car
// переменная х типа int
// переменная у типа int
void swap_car(car *list, int x, int y)
{
    car tmp;
    ident_car(&tmp);
    save_car(&list[x], &tmp);
    save_car(&list[y], &list[x]);
    save_car(&tmp, &list[y]);
}
// меняет местами значения полей list[x] и list[y]

// сохраняет значения полей из from в to
// Переменная len типа int
// Указатель на массив list типа key
double shell_car_sort(int len, car *list)
{
    int i, j, step;
    car tmp;
    clock_t start, end;
    start = clock();
    for (step = len / 2; step > 0; step /= 2)
        for (i = step; i < len; i++)
        {
            save_car(&list[i], &tmp);
            for (j = i; j >= step; j -= step)
            {
                if (tmp.price < list[j - step].price)
                {
                    save_car(&list[j-step], &list[j]);
                }
                else
                    break;
            }
            save_car(&tmp, &list[j]);
        }
    end = clock();
    return ((double)(end - start))/CLOCKS_PER_SEC;
}
// сортирует массив list по полю value и меняет переменную flag в положение 1(отсортировано)

// Переменная len типа int
// Указатель на массив list типа key
double buble_car_sort(int len, car *list)
{
    int i, j;
    clock_t start, end;
    start = clock();
    for (i = 0; i < len-1; i++)
        for (j = 0; j < len-i-1; j++)
            if (list[j].price > list[j+1].price)
                swap_car(list, j, j+1);
    end = clock();
    return ((double)(end - start))/CLOCKS_PER_SEC;
}
// сортирует массив list по полю value и меняет переменную flag в положение 1(отсортировано)

// указатель на массив list типа car
// переменная len типа int
// указатель на переменную flag типа int
void shuffle_car_list(car *list, int len)
{
    // инициализация генератора случайных чисел
    srand((unsigned)time(NULL));

    // реализация алгоритма перестановки
    for (int j = 0, i = len - 1; i >= 1; i--)
    {
        j = rand() % (i + 1);
        swap_car(list, j, i);
    }
}
// перемешивает массив list длины len и меняет переменную flag в положение 0(неотсортировано)

// указатель на массив list типа key
// переменная len типа int
// указатель на переменную flag типа int
void shuffle_key_list(key *list, int len)
{
    // инициализация генератора случайных чисел
    srand((unsigned)time(NULL));

    // реализация алгоритма перестановки
    for (int j = 0, i = len - 1; i >= 1; i--)
    {
        j = rand() % (i + 1);
        swap_key(list, j, i);
    }
}
// перемешивает массив list длины len и меняет переменную flag в положение 0(неотсортировано)
