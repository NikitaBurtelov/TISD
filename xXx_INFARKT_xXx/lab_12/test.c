#ifndef UTESTS_C
#define UTESTS_C
#include "routines.h"

int main(void)
{
    int nums[8] = {1980, 121, 11111, 123456, 1, 2, 666, 0};
    list_t listArr[4];
    for(int i = 0; i < 4; i++)
        { listArr[i].head = NULL; listArr[i].tail = NULL; listArr[i].listLen = 0; }

    for(int i = 0; i < 4; i++)
    {
        numToList(&(listArr[i]), nums[i]);
        printList(&(listArr[i]));
        freeList(&(listArr[i]));
    }

    for(int i = 0; i < 4; i++)
        { listArr[i].head = NULL; listArr[i].tail = NULL; listArr[i].listLen = 0; }

    for(int i = 4; i < 8; i++)
    {
        numToList(&(listArr[i-4]), nums[i]);
        printList(&(listArr[i-4]));
        freeList(&(listArr[i-4]));
    }

    return 0;
}

#endif // UTESTS_C
