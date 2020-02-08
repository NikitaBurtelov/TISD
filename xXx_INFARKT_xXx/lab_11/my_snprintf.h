#ifndef MY_SNPRINTF_H
#define MY_SNPRINTF_H

#include "converter.h"

long my_snprintf(char *str, size_t maxlen, const char *format, ...)
{
    va_list argptr;

    for(int i = 0; i < (int)strlen(str); i++)
        str[i] = 0;

    char *buf = calloc(sizeof (char) * strlen(format) + 1, sizeof (char)); // выделение памяти под буфер
    if (!buf)
        return -1;
    unsigned long buflen = strlen(format) + 1;

    va_start(argptr, format); // начало обхода по строке аргументов

    for(unsigned long i = 0, j = 0; format[i]; i++, j++) // начало обхода по символам строки str
    {                                                   // i - счетчик для buf, j - счетчик для format

        if (i > buflen) // проверка размера буфера
        {
            char *tmp = realloc(buf, ++buflen);
            if(!tmp)
            {
                return -1;
            }
            buf = tmp;
        }

        if(format[i] == '%')
        {
            i++;

            if     (format[i] == 'l' && (format[i+1] == 'd' || format[i+1] == 'i'))
            {
                long tmp = va_arg(argptr, long);
                char *stringedNum = convert(tmp, 10);
                if((strlen(stringedNum) + strlen(buf) + 2) > buflen)
                {
                    buflen = strlen(stringedNum) + buflen + 2;
                    char *tmp = realloc(buf, ++buflen);
                    if(!tmp)
                    {
                        return -1;
                    }
                    buf = tmp;
                }
                memcpy(&(buf[j]), stringedNum, strlen(stringedNum));
                j = strlen(buf) - 1;
                i++;
            }
            else if(format[i] == 'l' && format[i+1] == 'x')
            {
                long tmp = va_arg(argptr, long);
                char *stringedNum = convert(tmp, 16);
                if((strlen(stringedNum) + strlen(buf) + 2) > buflen)
                {
                    buflen = strlen(stringedNum) + buflen + 2;
                    char *tmp = realloc(buf, ++buflen);
                    if(!tmp)
                    {
                        return -1;
                    }
                    buf = tmp;
                }
                memcpy(&(buf[j]), stringedNum, strlen(stringedNum));
                j = strlen(buf) - 1;
                i++;
            }
            else if(format[i] == 'l' && format[i+1] == 'o')
            {
                long tmp = va_arg(argptr, long);
                char *stringedNum = convert(tmp, 8);
                if((strlen(stringedNum) + strlen(buf) + 2) > buflen)
                {
                    buflen = strlen(stringedNum) + buflen + 2;
                    char *tmp = realloc(buf, ++buflen);
                    if(!tmp)
                    {
                        return -1;
                    }
                    buf = tmp;
                }
                memcpy(&(buf[j]), stringedNum, strlen(stringedNum));
                j = strlen(buf) - 1;
                i++;
            }
            else if(format[i] == 'h' && (format[i+1] == 'd' || format[i+1] == 'i'))
            {
                int tmp = va_arg(argptr, int);
                char *stringedNum = convert(tmp, 10);
                if((strlen(stringedNum) + strlen(buf) + 2) > buflen)
                {
                    buflen = strlen(stringedNum) + buflen + 2;
                    char *tmp = realloc(buf, ++buflen);
                    if(!tmp)
                    {
                        return -1;
                    }
                    buf = tmp;
                }
                memcpy(&(buf[j]), stringedNum, strlen(stringedNum));
                j = strlen(buf) - 1;
                i++;
            }
            else if(format[i] == 'h' && format[i+1] == 'x')
            {
                int tmp = va_arg(argptr, int);
                char *stringedNum = convert(tmp, 16);
                if((strlen(stringedNum) + strlen(buf) + 2) > buflen)
                {
                    buflen = strlen(stringedNum) + buflen + 2;
                    char *tmp = realloc(buf, ++buflen);
                    if(!tmp)
                    {
                        return -1;
                    }
                    buf = tmp;
                }
                memcpy(&(buf[j]), stringedNum, strlen(stringedNum));
                j = strlen(buf) - 1;
                i++;
            }
            else if(format[i] == 'h' && format[i+1] == 'o')
            {
                int tmp = va_arg(argptr, int);
                char *stringedNum = convert(tmp, 8);
                if((strlen(stringedNum) + strlen(buf) + 2) > buflen)
                {
                    buflen = strlen(stringedNum) + buflen + 2;
                    char *tmp = realloc(buf, ++buflen);
                    if(!tmp)
                    {
                        return -1;
                    }
                    buf = tmp;
                }
                memcpy(&(buf[j]), stringedNum, strlen(stringedNum));
                j = strlen(buf) - 1;
                i++;
            }
            else if(format[i] == 'd' || format[i] == 'i')
            {
                int tmp = va_arg(argptr, int);
                char *stringedNum = convert(tmp, 10);
                if((strlen(stringedNum) + strlen(buf) + 2) > buflen)
                {
                    buflen = strlen(stringedNum) + buflen + 2;
                    char *tmp = realloc(buf, ++buflen);
                    if(!tmp)
                    {
                        return -1;
                    }
                    buf = tmp;
                }
                memcpy(&(buf[j]), stringedNum, strlen(stringedNum));
                j = strlen(buf) - 1;
            }
            else if(format[i] == 'x')
            {
                int tmp = va_arg(argptr, int);
                char *stringedNum = convert(tmp, 16);
                if((strlen(stringedNum) + strlen(buf) + 2) > buflen)
                {
                    buflen = strlen(stringedNum) + buflen + 2;
                    char *tmp = realloc(buf, ++buflen);
                    if(!tmp)
                    {
                        return -1;
                    }
                    buf = tmp;
                }
                memcpy(&(buf[j]), stringedNum, strlen(stringedNum));
                j = strlen(buf) - 1;
            }
            else if(format[i] == 'o')
            {
                int tmp = va_arg(argptr, int);
                char *stringedNum = convert(tmp, 8);
                if((strlen(stringedNum) + strlen(buf) + 2) > buflen)
                {
                    buflen = strlen(stringedNum) + buflen + 2;
                    char *tmp = realloc(buf, ++buflen);
                    if(!tmp)
                    {
                        return -1;
                    }
                    buf = tmp;
                }
                memcpy(&(buf[j]), stringedNum, strlen(stringedNum));
                j = strlen(buf) - 1;
            }
            else if(format[i] == 'c')
            {
                long tmp = va_arg(argptr, long);
                if((strlen(buf) + 2) > buflen)
                {
                    buflen = buflen + 2;
                    char *tmp = realloc(buf, ++buflen);
                    if(!tmp)
                    {
                        return -1;
                    }
                    buf = tmp;
                }
                buf[j] = (char)tmp;
                buf[j+1] = 0;
            }
            else if(format[i] == 's')
            {
                char *tmp = va_arg(argptr, char *);
                if((strlen(buf) + strlen(tmp) + 2) > buflen)
                {
                    buflen = buflen + 2;
                    char *tmp = realloc(buf, ++buflen);
                    if(!tmp)
                    {
                        return -1;
                    }
                    buf = tmp;
                }
                memcpy(&(buf[j]), tmp, strlen(tmp));
                j = strlen(buf) - 1;
            }
        }
        else
        {
            buf[j] = format[i];
            buf[j+1] = 0;
        }
    }

    memcpy(str, buf, maxlen);
    str[maxlen - 1] = 0;
    buflen = strlen(buf);
    free(buf);
    return buflen;
}

#endif // MY_SNPRINTF_H
