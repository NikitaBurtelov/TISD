#include "functins.h"

void ident_bufer(string bufer)
{
    for (int i = 0; i < STRLEN; i++)
    {
        bufer[i] = 0;
    }
}

int readSentence(FILE *fp, sentence *sentence, uniqWords uniqWords)
{
    char bufer[2048];
    int len;
    if (!feof(fp))
    {
        ident_bufer(bufer);
        fgets(bufer, STRLEN, fp);
        if(strlen(bufer) == 0)
            return EOF;
        len = (int)strlen(bufer) - 1;
        bufer[len] = 0;
    }
    else // если конец файла
        return EOF;

    int wordsNum = 1;
    if(len) // подсчет количества слов, если длина не нулевая
    {
        for(int i = 0; i < len; i++)
            if(bufer[i] == ' ')
                wordsNum++;
    }
    else // если вместо предложения пустая строка
        return EOF;

    sentence->words = malloc(WORDLEN * (unsigned)wordsNum); // выделяем место под массива слов в предложении

    int i = 0;
    while(sscanf(bufer, "%s", sentence->words[i])) // пока считывание удачно
    {
        i++;
        sentence->lenght = i;
    }

    sentence->binWords = malloc(sizeof (bool) * (unsigned)uniqWords.lenght);
    for(int i = 0; i < uniqWords.lenght; i++) // заполняем массив sentence.binWords
        for(int j = 0; j < sentence->lenght; i++)
            if(strcmp(sentence->words[j], uniqWords.words[i]) == 0) // если нет различий между j-тым словом
                                                                    // из предложения и i-тым словом из массива уникальных слов
                sentence->binWords[i] = 1;                          // то ставим единицу
            else
                sentence->binWords[i] = 0;                          // иначе ноль

    return EXIT_SUCCESS;
}

void checkWord(string word, uniqWords *uniqWords) // проверяет уникальное ли это слово, если да, то добавляет в массив уникальных слов
{
    for (int i = 0; i < uniqWords->lenght; i++)
        if(strcmp(word, uniqWords->words[i]) != 0) // если есть различия между словами
        {
            uniqWords->lenght++;
            uniqWords->words = realloc(uniqWords->words, sizeof(uniqWords->words) * (unsigned)(uniqWords->lenght + 1));
            strcpy(uniqWords->words[uniqWords->lenght - 1], word);
        }
}
