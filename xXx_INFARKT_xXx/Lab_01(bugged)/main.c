#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define BUF_LEN 60

#define OVERFLOW 2
#define NON_VALID_CHAR 3
#define WRONG_NUMBER_FORMAT 5
#define DIVISION_BY_ZERO 6
#define MANTISSA_OVERFLOW 7
#define NON_INT_NUM 8

#define MANT_LEN 35
#define MAX_ORD 100000

typedef char bufer[BUF_LEN];

// Представление числа структурой
struct number {
    // Порядок числа: целочисленное значение (10000; -10000)
    int ord;
    // Знак числа: 1 - '+', -1 - '-'
    short int sign;
    // Мантисса числа в виде массива символов
    char mantiss[MANT_LEN];
};

// Проверка ошибок
int valid_check(int err_flag);

// Идентификация структуры числа
void ident_num(struct number *p);

// Идентификация буфера
void ident_buf(bufer b);

// Преобразование числа из массива символов в предопределенную структуру
int num_reconstruct(struct number *p, bufer b);
int num_reconstruct_int(struct number *p, bufer b);

// Функция вывода числа в научной форме
void num_out(struct number *p);

// Деление
int my_division(struct number *p1, struct number *p2, struct number *res);

int main(void)
{
    struct number frst;
    struct number scnd;
    struct number res;
    bufer b;
    int error_flag; // флаг ошибок

    ident_buf(b);
    ident_num(&frst);
    printf("                              ---------|---------|---------|\n");
    printf("Input the divised real number:");
    scanf("%s", b);
    error_flag = num_reconstruct(&frst, b);
    if (valid_check(error_flag) == EXIT_FAILURE)
        return EXIT_FAILURE;

    ident_buf(b);
    ident_num(&scnd);
    printf("                              ---------|---------|---------|\n");
    printf("Input the divisor real number:");
    scanf("%s", b);
    error_flag = num_reconstruct(&scnd, b);
    if (valid_check(error_flag) == EXIT_FAILURE)
        return EXIT_FAILURE;

    if (strlen(scnd.mantiss) == 0)
        error_flag = DIVISION_BY_ZERO;
    if (valid_check(error_flag) == EXIT_FAILURE)
        return EXIT_FAILURE;

    if (strlen(frst.mantiss) == 0)
    {
        printf("Result: ");
        printf("0\n");
        return EXIT_SUCCESS;
    }
    else
    {
        ident_num(&res);
        error_flag = my_division(&frst, &scnd, &res);
        if (valid_check(error_flag) == EXIT_FAILURE)
            return EXIT_FAILURE;
        printf("Result: ");
        num_out(&res);
    }

    return EXIT_SUCCESS;
}

void ident_num(struct number *p)
{
    for(int i = 0; i < MANT_LEN; i++)
        p->mantiss[i] = '\0';

    p->ord = 0;
    p->sign = 0;
}

void ident_buf(bufer b)
{
    for(int i = 0; i < BUF_LEN; i++)
        b[i] = '\0';
}

void num_out(struct number *p)
{
    if(p->sign > 0)
        printf("+");
    else
        printf("-");
    printf("0.%se%d\n", p->mantiss, p->ord);
}

int valid_check(int err_flag)
{
    if (err_flag == OVERFLOW)
    {
        printf("Overflow!\n");
        return EXIT_FAILURE;
    }
    else if(err_flag == NON_VALID_CHAR)
    {
        printf("Non valid symbol!\n");
        return EXIT_FAILURE;
    }
    else if(err_flag == WRONG_NUMBER_FORMAT)
    {
        printf("Wrong number format!\n");
        return EXIT_FAILURE;
    }
    else if(err_flag == MANTISSA_OVERFLOW)
    {
        printf("Mantissa overflow!\n");
        return EXIT_FAILURE;
    }
    else if(err_flag == DIVISION_BY_ZERO)
    {
        printf("Division by zero!\n");
        return EXIT_FAILURE;
    }
    else if(err_flag == NON_INT_NUM)
    {
        printf("Real number inputed!\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int num_reconstruct(struct number *p, bufer b)
{
    // Буфер порядка
    bufer ord;
    ident_buf(ord);

    // Счетчики символов в буфере и мантиссе соответственно
    int i = 0, j = 0;

    // Знак порядка
    int ord_sign = 0;

    // Флаги для точки, знака мантиcсы, позиции точки
    int comma_flag = 0;
    int mant_flag = 0;
    int comma_pos = -1;

    // Определяем знак мантиссы
    if (b[i] == '-')
    {
        p->sign = -1;
        mant_flag = 1;
        i++;
    }
    else if (b[i] == '+')
    {
        p->sign = 1;
        mant_flag = 1;
        i++;
    }
    else
    {
        p->sign = 1;
    }

    // Если не цифра и не точка, то ошибка
    if (!('0' >= b[i] || b[i] <= '9' || b[i] == '.'))
    {
        return NON_VALID_CHAR;
    }

    // Цикл обработки мантиссы
    while(b[i] != 'E' && b[i] != 'e' && b[i] != '\0')
    {
        // Проверка на то цифра ли это
        if (('0' <= b[i] && b[i] <= '9') && b[i] != '.')
        {
        // Если это цифра то записываем ее в мантиссу и увеличиваем счетчик мантиссы
            p->mantiss[j] = b[i];
            j++;
        }
        // Если это точка, то пропускаем ее и запоинмаем позицию, если встречается повторно, то ошибка
        else if (b[i] == '.' && comma_flag == 0)
        {
            comma_flag = 1;
            comma_pos = i;
        }
        else return NON_VALID_CHAR;

        // Переход к следующему символу
        i++;

        // Если мантисса заполнена, а цифры остались то ошибка
        // Если не точка, не цифра, не буква 'E' или 'e', то ошибка
        if ((b[i] != '.') && (b[i] != 'E') && (b[i] != 'e') && (j == 31))
            return MANTISSA_OVERFLOW;
    }

    // Пропуск 'E' или 'e'
    if (b[i] == 'e' || b[i] == 'E')
    {
        i++;
    }

    // Если длина мантиссы 0 то ошибка
    if (strlen(p->mantiss) == 0)
        return WRONG_NUMBER_FORMAT;

    // Определяем знак порядка
    if (b[i] == '-')
    {
        ord_sign = -1;
        i++;
    }
    else if (b[i] == '+')
    {
        ord_sign = 1;
        i++;
    }
    else ord_sign = 1;

    // Обнуляем счетчик
    j = 0;

    // Обработка порядка числа
    while(b[i])
    {
        // Проверка на то цифра ли это
        if ('0' <= b[i] && b[i] <= '9')
        {
        // Если это цифра то записываем ее в порядок и увеличиваем счетчик порядка
        // Иначе ошибка
            ord[j] = b[i];
            j++;
        }
        else return NON_VALID_CHAR;

        // Переход к следующему символу
        i++;
    }

    // Если на вводе значение экспоненты выходит за граничные значения то возврат ошибки
    p->ord = atoi(ord);
    if (p->ord <= -MAX_ORD || p->ord >= MAX_ORD)
        return OVERFLOW;

    // Смещение точки до упора вправо

    p->ord *= ord_sign;
    if (comma_pos >= 0)
        p->ord -= (int)strlen(p->mantiss) - comma_pos + mant_flag;

    // Удаление незначащих нулей слева
    while(p->mantiss[0] == '0')
    {
        int n = (int)strlen(p->mantiss);
        for(int i = 0; i < n; i++)
        {
            p->mantiss[i] = p->mantiss[i+1];
        }
    }

    // Смещение точки до упора влево
    p->ord += (int)strlen(p->mantiss);

    // Удаление незначащих нулей справа
    i = (int)strlen(p->mantiss);
    while(p->mantiss[strlen(p->mantiss) - 1] == '0')
    {
        p->mantiss[i] = '\0';
        i--;
    }

    return EXIT_SUCCESS;
}

int num_reconstruct_int(struct number *p, bufer b)
{
    // Буфер порядка
    bufer ord;
    ident_buf(ord);

    // Счетчики символов в буфере и мантиссе соответственно
    int i = 0, j = 0;

    // Знак порядка
    int ord_sign = 0;

    // Флаг для "E" или "e"
    int e_flag = 0;

    // Флаги для точки, знака мантиcсы, позиции точки
    int comma_flag = 0;
    int mant_flag = 0;
    int comma_pos = -1;

    // Определяем знак мантиссы
    if (b[i] == '-')
    {
        p->sign = -1;
        mant_flag = 1;
        i++;
    }
    else if (b[i] == '+')
    {
        p->sign = 1;
        mant_flag = 1;
        i++;
    }
    else
    {
        p->sign = 1;
    }

    // Если не цифра и не точка, то ошибка
    if (!('0' >= b[i] || b[i] <= '9' || b[i] == '.'))
    {
        return NON_VALID_CHAR;
    }

    // Цикл обработки мантиссы
    while(b[i] != 'E' && b[i] != 'e' && b[i] != '\0')
    {
        // Проверка на то цифра ли это
        if (('0' <= b[i] && b[i] <= '9') && b[i] != '.')
        {
        // Если это цифра то записываем ее в мантиссу и увеличиваем счетчик мантиссы
            p->mantiss[j] = b[i];
            j++;
        }
        // Если это точка, то пропускаем ее и запоинмаем позицию, если встречается повторно, то ошибка
        else if (b[i] == '.' && comma_flag == 0)
        {
            comma_flag = 1;
            comma_pos = i;
        }
        else return NON_VALID_CHAR;

        // Переход к следующему символу
        i++;

        // Если мантисса заполнена, а цифры остались то ошибка
        // Если не точка, не цифра, не буква 'E' или 'e', то ошибка
        if ((b[i] != '.') && (b[i] != 'E') && (b[i] != 'e') && (j == 31))
            return MANTISSA_OVERFLOW;
    }

    // Пропуск 'E' или 'e'
    if (b[i] == 'e' || b[i] == 'E')
    {
        i++;
        e_flag = 1;
    }

    // Если длина мантиссы 0 то ошибка
    if (strlen(p->mantiss) == 0)
        return WRONG_NUMBER_FORMAT;

    // Определяем знак порядка
    if (b[i] == '-')
    {
        ord_sign = -1;
        i++;
    }
    else if (b[i] == '+')
    {
        ord_sign = 1;
        i++;
    }
    else ord_sign = 1;

    // Обнуляем счетчик
    j = 0;

    // Обработка порядка числа
    while(b[i])
    {
        // Проверка на то цифра ли это
        if ('0' <= b[i] && b[i] <= '9')
        {
        // Если это цифра то записываем ее в порядок и увеличиваем счетчик порядка
        // Иначе ошибка
            ord[j] = b[i];
            j++;
        }
        else return NON_VALID_CHAR;

        // Переход к следующему символу
        i++;
    }

    // Если на вводе значение экспоненты выходит за граничные значения то возврат ошибки
    if (p->ord <= -MAX_ORD || p->ord >= MAX_ORD)
        return OVERFLOW;

    // Смещение точки до упора вправо
    p->ord = atoi(ord);
    p->ord *= ord_sign;
    if (comma_pos >= 0)
        p->ord -= (int)strlen(p->mantiss) - comma_pos + mant_flag;

    // Удаление незначащих нулей слева
    while(p->mantiss[0] == '0')
    {
        int n = (int)strlen(p->mantiss);
        for(int i = 0; i < n; i++)
        {
            p->mantiss[i] = p->mantiss[i+1];
        }
    }

    // Смещение точки до упора влево
    p->ord += (int)strlen(p->mantiss);

    // Удаление незначащих нулей справа
    i = (int)strlen(p->mantiss);
    while(p->mantiss[strlen(p->mantiss) - 1] == '0')
    {
        p->mantiss[i] = '\0';
        i--;
    }

    if(e_flag == 1 || comma_flag == 1)
        return NON_INT_NUM;

    return EXIT_SUCCESS;
}

int my_division(struct number *p1, struct number *p2, struct number *res)
{
    // Счетчики
    int i = 0, j = 0, k = 0;
    // Длина делимого
    int divr = (int)strlen(p1->mantiss);
    // Длина делителя
    int divl = (int)strlen(p2->mantiss);
    // Флаг вычитания
    int flag = 0;

    // пока не достигнута нужная точность или остаток не равен нулю
    while (strlen(res->mantiss) <= 31 && (strlen(p1->mantiss) != 0))
    {
        // Зануление флага на возможность вычитания
        flag = 0;
        // Зануление разряда результата
        res->mantiss[j] = '0';

        if (p1->mantiss[0] != '0')
        {
            // Cнос нуля при необходимости
            if (divr < divl)
            {
                p1->mantiss[divr] = '0';
                divr++;
            }
            else if (divr == divl)
            {
                i = 0;
                while (p2->mantiss[i])
                {
                    if (p2->mantiss[i] == p1->mantiss[i])
                    {
                        i++;
                    }
                    else if(p2->mantiss[i] < p1->mantiss[i])
                    {
                        flag = 1;
                        break;
                    }
                    else
                    {
                        p1->mantiss[divr] = '0';
                        divr++;
                        break;
                    }
                }
            }

            // Проверка на возможность вычитания
            i = 0;
            if (divr >= divl && flag == 0)
            {
                while (1)
                    if (p2->mantiss[i])
                    {
                        if (p2->mantiss[i] > p1->mantiss[i])
                        {
                            flag = 0;
                            break;
                        }
                        else if (p2->mantiss[i] == p1->mantiss[i])
                        {
                            i++;
                        }
                        else
                        {
                            flag = 1;
                            break;
                        }
                    }
                    else
                    {
                        flag = 1;
                        break;
                    }
            }

            // Сдвиг вычитаемого на 1 разряд вправо при необходимости
            if (divr > divl && flag == 0)
            {
                for(i = divl; i >= 0; i--)
                {
                    p2->mantiss[i + 1] = p2->mantiss[i];
                }
                p2->mantiss[0] = '0';
                divl++;
                flag = 1;
            }
            else if (j == 0 && ((p1->mantiss[0] != '1' || p1->mantiss[1] != '0')))
                res->ord++;
            else if(j == 0 && p2->mantiss[0] == '1' && p2->mantiss[1] == '1' &&
                    p2->mantiss[strlen(p2->mantiss) - 1] > p1->mantiss[strlen(p2->mantiss) - 1] &&
                    divr < divl)
                res->ord++;

            // Вычитание
            while(flag == 1)
            {
                for(i = divl - 1; i >= 0; i--)
                {
                    p1->mantiss[i] -= p2->mantiss[i] - '0';
                    if (p1->mantiss[i] < '0')
                        {
                            p1->mantiss[i] += 10;
                            p1->mantiss[i-1]--;
                        }
                }
                // Прибавление единицы в разряд результата
                res->mantiss[j]++;

                // Проверка на возможность дальнейшего вычитания (уменьшаемое >= вычитаемое)
                for(i = 0; i <= divl;)
                {
                    if(p1->mantiss[i] < p2->mantiss[i])
                    {
                        flag = -1;
                        break;
                    }
                    else if(p1->mantiss[i] == p2->mantiss[i])
                        i++;
                    else
                        break;
                }
            }

            // Сдвиг до упора влево
            if(p1->mantiss[0] == '0' && p2->mantiss[0] == '0')
            {
                for(i = 0; i < divr; i++)
                {
                    p1->mantiss[i] = p1->mantiss[i + 1];
                }
                for(i = 0; i < divl; i++)
                {
                    p2->mantiss[i] = p2->mantiss[i + 1];
                }
                p1->mantiss[divr] = '\0';
                p2->mantiss[divl] = '\0';
                divr--;
                divl--;

            }

            if(p1->mantiss[0] == '0' && divr == divl)
            {
                for(i = 0; i < divr; i++)
                    p1->mantiss[i] = p1->mantiss[i + 1];
                divr--;
            }

        }
        // Снос числа
        if(p1->mantiss[0] == '0')
        {
            if(divr == divl)
            {
                j--;
            }
            for(i = 0; i < divr; i++)
                p1->mantiss[i] = p1->mantiss[i + 1];
            divr--;
        }

        // Перемещение к следующему разряду результата
        if (res->mantiss[0] != '0')
            j++;
    }

    // Округление
    if(res->mantiss[30] >= '5')
    {
        res->mantiss[30] = '\0';
        res->mantiss[29]++;
    }
    else
        res->mantiss[30] = '\0';

    // Проверка на девятки в конце
    flag = 0;
    i = (int)strlen(res->mantiss) - 1;
    if(strlen(res->mantiss) >= 30)
        while(res->mantiss[i] >= '9')
        {
            res->mantiss[i] = '0';
            i--;
            flag = 1;
            if(i < 0)
            {
                for(k = i; k >= 0; k--)
                    res->mantiss[k] = '\0';
                res->mantiss[0] = '0';
                break;
            }
        }
    if(flag == 1)
        res->mantiss[i]++;

    // Подсчет порядка
    res->ord += p1->ord - p2->ord;
    if(abs(res->ord) >= 100000)
        return OVERFLOW;

    // Знак результата
    if(p1->sign == p2->sign)
        res->sign = 1;
    else
        res->sign = -1;

    for(i = (int)strlen(res->mantiss) - 1; i>= 0; i--)
        if(res->mantiss[i] == '0')
            res->mantiss[i] = '\0';
        else
            break;

    if(strlen(res->mantiss) == 0)
    {
        res->mantiss[0] = '1';
        res->ord++;
    }

    return EXIT_SUCCESS;
}
