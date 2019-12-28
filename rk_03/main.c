#include "functins.h"

int main()
{
    uniqWords uniqWords;
    sentence *sentenceString;
    FILE *fp;
    fp = fopen("in.txt", "r");
    char string[2048];
    int sentenceStringLen = 0;

    uniqWords.words = malloc(sizeof(string));
    uniqWords.lenght = 1;

    while(fgets(string, 2048, fp ) != NULL)
    {
        sentenceStringLen++;
    }

    fclose(fp);
    fp = fopen("in.txt", "r");
    sentenceString = malloc(sizeof(sentence) * (size_t)sentenceStringLen);

    int i = 0;
    while(readSentence(fp, &sentenceString[i], uniqWords) != EOF)
    {
        for(int j = 0; j < sentenceString[i].lenght; j++)
            checkWord(sentenceString[i].words[j], &uniqWords);
        i++;
        sentenceStringLen++;
    }

    free(uniqWords.words);
    for(int k = 0; k < sentenceStringLen; k++)
    {
        free(sentenceString[k].words);
        free(sentenceString[k].binWords);
    }

    fclose(fp);
    return 0;
}
