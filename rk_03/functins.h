#ifndef FUNCTINS_H
#define FUNCTINS_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STRLEN 2048
#define WORDLEN 128
#define UNIQ 100
#define NON_UNIQ 101

typedef char string[STRLEN];

typedef struct
{
    char **words;          // массив уникалных слов текста отсортированный в лексико графическом порядке
    int lenght;             // длина массива
} uniqWords;

typedef struct
{
    char **words;          // массив слов в предложении в порядке следования
    int lenght;             // количество слов в предложении
    bool *binWords;         // бинарный массив слов длины uniqWords.leght; на i-том месте: 1 - если слово есть в предложении, 0 - если нет
} sentence;

void ident_bufer(string bufer);

int readSentence(FILE *fp, sentence *sentence, uniqWords uniqWords);

void checkWord(string word, uniqWords *uniqWords); // проверяет уникальное ли это слово, если да, то добавляет в массив уникальных слов

#endif // FUNCTINS_H

