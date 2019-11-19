#ifndef TYPES_H
#define TYPES_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Ошибки
#define CANT_READ_FILE 2
#define CANT_READ_STR 3
#define FILE_NOT_EXISTS 4
#define EMPTY_FILE 5
#define OPERATION_ABORTED 6
#define WRONG_MODE 7
#define NO_CHANGES 8

#define STRLEN 256
#define LISTLEN 2000

typedef struct // структура в которой хранится время сортировок
{
    double buble_keys; // время сортировки пузырьком ключей
    double buble_cars; // время сортировки пузырьком записей
    double shell_keys; // время сортировки сорт. Шелла ключей
    double shell_cars; // время сортировки сорт. Шелла записей
} times;

typedef struct
{
    int base_flag;  // 0 - нет открытого файла; 1 - есть открытый файл
    int keys_flag;  // 0 - несортировано; 1 - сортировано
    int car_flag;   // 0 - несортировано; 1 - сортировано
    int chages_flag; // 0 - нет изменений в базе: 1 - есть изменения в базе
} flags; // флаги нужные для работы программы

typedef struct
{
  int id;
  int value;
} key; // ключ записи

typedef char str[STRLEN]; // строковая переменная

// реализация перегрузки функции в си: флаг - тип переменной, юнион value - значение переменной
typedef struct
{
    int flag; // флаг выбора поля: строка(0) или число(1)
    union // вариативное поле для хранения значения
    {
        str buf;
        long _int_;
    }value;
} choose;

typedef struct
{
    int id; // уникальный идентификатор элеменета
    int empt; // Флаг, отвечающий за действительность записи: 0 - недействительна, 1 - действительна
    str model; // Модель
    str country; // Страна
    str colour; // Цвет
    int price; // Цена
    int cond_flag; // Флаг отвечащий за состояние машины: б/у(1) или новая(0)

    // Вариативная часть которая описывает параметры машины в зависимости от  "cond_flag"
    union
    {
        struct // Параметры машины б/у
        {
            long run; // Пробег
            int year; // Год выпуска
            int repairs; // Количество починок
            int users; // Количество собственников
        } used_s;

        struct // Параметры новой машины
        {
            int guarantee; // Длительность гарантии
        } new_s;
    } condition;
} car;

#endif // TYPES_H
