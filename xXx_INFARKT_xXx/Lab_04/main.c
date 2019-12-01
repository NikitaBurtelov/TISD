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
               "5.Task                          10.Task                     0.Exit\n");
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
        case 5:
        {
            int strLen = 0;
            printf("Input length of the string: ");
            if(scanf("%d", &strLen) != 1)
            {
                clear();
                printf("Wrong Input!\n");
                break;
            }
            if(strLen <= 0)
            {
                printf("Wrong Input!\n");
                break;
            }

            char *expression = NULL;
            char data;
            expression = malloc(sizeof (char) * ((unsigned)strLen + 1));
            strLen++;
            if(!expression)
            {
                printf("Memory allocation error!\n");
                break;
            }

            printf("Input string with brackets('()' or '[]' or '{}') and without spacebars; maximum length = %d: ", strLen - 1);
            if(scanf("%s", expression) != 1)
            {
                printf("Wrong Input!\n");
                break;
            }
            expression[strLen] = 0;

            arrStack_t bracketsStack1; // для (
            arrStack_t bracketsStack2; // для [
            arrStack_t bracketsStack3; // для {
            int sum1 = 0, sum2 = 0, sum3 = 0, flag = 0;
            initArr(&bracketsStack1, sizeof (char) * (unsigned)strLen);
            initArr(&bracketsStack2, sizeof (char) * (unsigned)strLen);
            initArr(&bracketsStack3, sizeof (char) * (unsigned)strLen);

            for(int i = 0; expression[i] && (i < strLen); i++)
            {
                if(expression[i] == '(')
                {
                    //arrPush(&bracketsStack1, &expression[i]);
                    sum1++;
                }
                else if(expression[i] == '[')
                {
                    //arrPush(&bracketsStack2, &expression[i]);
                    sum2++;
                }
                else if(expression[i] == '{')
                {
                    //arrPush(&bracketsStack3, &expression[i]);
                    sum3++;
                }

                else if(expression[i] == ')')
                {
                    //arrPop(&bracketsStack1, &data);
                    sum1--;
                }
                else if(expression[i] == ']')
                {
                    //arrPop(&bracketsStack2, &data);
                    sum2--;
                }
                else if(expression[i] == '}')
                {
                    //arrPop(&bracketsStack3, &data);
                    sum3--;
                }

                if(sum1 < 0 || sum2 < 0 || sum3 < 0)
                {
                    printf("Ne Verno!\n");
                    flag++;
                    break;
                }
            }
            if(flag)
                break;

            if(sum1 == 0 && sum2 == 0 && sum3 == 0)
                printf("Verno!\n");
            else
                printf("Ne Verno!\n");

            freeArr(&bracketsStack1);
            freeArr(&bracketsStack2);
            freeArr(&bracketsStack3);

            break;
        }
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
