#include "routines.h"

int main()
{
    int num1 = 0, num2 = 0;
    char key[256];
    list_t list = {NULL, NULL, 0};

    printf("in>\n");
    if(scanf("%s", key) != 1)
        return -1;

    if(!strcmp(key, "out"))
    {
        if(scanf("%d", &num1) != 1)
            return -1;
        numToList(&list, num1);
        printf("<out\n");
        printList(&list);
    }
    else if(!strcmp(key, "mul"))
    {
        if(scanf("%d %d", &num1, &num2) != 2)
            return -1;
        num1 *= num2;
        if(!num1)
            return -1;
        numToList(&list ,num1);
        printf("<out\n");
        printList(&list);
    }
    else if(!strcmp(key, "sqr"))
    {
        if(scanf("%d", &num1) != 1)
            return -1;
        num1 *= num1;
        if(!num1)
            return -1;
        numToList(&list, num1);
        printf("<out\n");
        printList(&list);
    }
    else if(!strcmp(key, "div"))
    {
        if(scanf("%d %d", &num1, &num2) != 2)
            return -1;
        num1 /= num2;
        if(!num1)
            return -1;
        numToList(&list, num1);
        printList(&list);
    }
    else
        return -1;

    freeList(&list);
    return 0;
}
