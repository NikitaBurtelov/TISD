#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/mazeGen.h"
#include "headers/stackArrRoutines.h"
#include "headers/stackListRoutines.h"

int main(void)
{
    cell item = {2, 2};

    arrStack_t array;
    initArr(&array, sizeof (int));

    listStack_t list;
    initList(&list);

    int ch = 1;
    while(ch)
    {
        printf("\n    Array stack menu:             List stack menu:\n"
               "1.Stack status                  6.Stack status\n"
               "2.Push                          7.Push\n"
               "3.Pop                           8.Pop\n"
               "4.Peek                          9.Peek\n"
               "                                10.Task                     0.Exit\n");
        printf("        Input:");

        int rc = scanf("%d", &ch);

        if(rc != 1 || ch < -1 || ch > 10)
        {
            ch = -1;
        }
        switch (ch)
        {
        case 1:
            arrStatus(&array);
            break;
        case 2:
            if(array.curr == array.top)
                printf("Stack overflow!\n");
            else
            {
                printf("Input integer:");
                clear();
                scanf("%d", &item.x);
                arrPush(&array, &item);
                clear();
            }
            break;
        case 3:
            if(array.curr == array.bot)
                printf("Stack is empty\n");
            else
            {
                arrPop(&array, &item);
                printf("Popped value = %d\n", item.x);
            }
            break;
        case 4:
            if(array.curr == array.bot)
                printf("Stack is empty\n");
            else
            {
                arrPeek(&array, &item);
                printf("Peeked value = %d\n", item.x);
            }
            break;
        case 6:
            listStatus(&list);
            break;
        case 7:
            if(list.stackLen == STACK_LEN)
                printf("Stack overflow!\n");
            else
            {
                printf("Input symbol:");
                clear();
                scanf("%d", &item.x);
                listPush(&list, &item);
                clear();
            }
            break;
        case 8:
            if(list.stackLen == 0)
                printf("Stack is empty!\n");
            else
            {
                listPop(&list, &item);
                printf("Popped value = %d\n", item.x);
            }
            break;
        case 9:
            if(list.head == NULL)
                printf("Stack is empty!\n");
            else
            {
                listPeek(&list, &item);
                printf("Peeked value = %d\n", item.x);
            }
            break;
        case 10:
        {
            system("konsole -e ./Debug/mazeMain.exe");
            break;
        }
        default:
            if(ch != 0)
            {
                clear();
                printf("Wrong input!\n");
            }
            break;
        }
    }
    return EXIT_SUCCESS;
}
