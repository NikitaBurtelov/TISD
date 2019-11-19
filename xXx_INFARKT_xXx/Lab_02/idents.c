#include "includes/idents.h"

// указатель на объект типа car
void ident_car(car *new_car)
{
    new_car->empt = 0;
    new_car->cond_flag = 0;
    new_car->price = 0;
    for(int i = 0; i < STRLEN; i++)
    {
        new_car->model[i] = 0;
        new_car->colour[i] = 0;
        new_car->country[i] = 0;
    }
    new_car->condition.used_s.run = 0;
    new_car->condition.used_s.year = 0;
    new_car->condition.used_s.users = 0;
    new_car->condition.used_s.repairs = 0;
}
// объявляет объект new_car типа car недействительным

// указатель на массив типа str
void ident_bufer(str bufer)
{
    for (int i = 0; i < STRLEN; i++)
    {
        bufer[i] = 0;
    }
}
// зануляет все элементы строки buf

// массив объектов типа car
void ident_list(car *list)
{
    for(int i = 0; i < LISTLEN; i++)
        ident_car(&list[i]);
}
// делает все объекты массива list типа car недействительными

// указатель на переменную типа key
void ident_key(key *x)
{
    x->id = 0;
    x->value = 0;
}
// зануляет все поля перемнной key

void ident_flags(flags *flag)
{
    flag->car_flag = 0;
    flag->base_flag = 0;
    flag->keys_flag = 0;
}

void ident_key_list(key *list)
{
    for(int i = 0; i < LISTLEN; i++)
        ident_key(&list[i]);
}
