#ifndef CONVERTER_H
#define CONVERTER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

// перевод числа num в строку (до 16-ричной СС включительно)
char digit(long num)
{
  switch (num) {
  case 0: return '0';
  case 1: return '1';
  case 2: return '2';
  case 3: return '3';
  case 4: return '4';
  case 5: return '5';
  case 6: return '6';
  case 7: return '7';
  case 8: return '8';
  case 9: return '9';
  case 10: return 'a';
  case 11: return 'b';
  case 12: return 'c';
  case 13: return 'd';
  case 14: return 'e';
  case 15: return 'f';
  default: return 0;
  }
}

// Получение целой части числа
long dectox_long(long a, long p, char *s)
{
  long num = (long)a;
  long rest = num % p;
  num /= p;
  if (num == 0)
  {
    s[0] = digit(rest); return 1;
  }
  long k = dectox_long(num, p, s);
  s[k++] = digit(rest);
  return k;
}

// Получение дробной части числа
void dectox_double(double a, long p, char *s)
{
  long iter = 0;
  long k = 0;
  double a1 = a;
  do {
    a1 = a1 * p;
    long num = (long)(a1);
    s[k++] = digit(num);
    a1 -= (long)a1;
    iter++;
  } while (a1 > 0.00000001 && iter < 10);
  s[k] = '\0';
}

// Возвращает конвертированное число a в СС p в виде строки
char *convert(double a, long p)
{
    char s[80] = { 0 };
    long k;
    if(a < 0)
        k = dectox_long((long)(a*(-1)), p, s);
    else
        k = dectox_long((long)a, p, s);
    s[k++] = ',';
    dectox_double(a - (long)a, p, &s[k]);
    for(long i = 0; i < 80; i++)
        if(s[i] == ',')
        {
            s[i] = 0;
            break;
        }
    char *res = calloc(80, sizeof (char));
    if(a < 0)
    {
        res[0] = '-';
        memcpy(&(res[1]), s, 80 * sizeof (char));
    }
    else
        memcpy(res, s, 80 * sizeof (char));
    return res;
}


#endif // CONVERTER_H
