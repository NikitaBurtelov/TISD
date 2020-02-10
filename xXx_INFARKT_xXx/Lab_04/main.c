#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "headers/mazeGen.h"
#include "headers/stackArrRoutines.h"
#include "headers/stackListRoutines.h"

double arrCheck(char *expression, char *result)
{
    arrStack_t exp;
    char tmp = 0, breakflag = 0;
    initArr(&exp, sizeof (char));

    clock_t start = clock();
    for(unsigned i = 0; i < strlen(expression); i++)
    {
        if(expression[i] == '(' || expression[i] == '[' || expression[i] == '{')
            arrPush(&exp, &expression[i]);
        else if (expression[i] == ')')
        {
            if(arrPeek(&exp, &tmp) == EXIT_SUCCESS)
            {
                if(tmp == '(')
                {
                    arrPop(&exp, &tmp);
                }
                else
                {
                    sprintf(result, "Non valid expression!\n");
                    breakflag++;
                    break;
                }
            }
            else
            {
                sprintf(result, "Non valid expression!\n");
                breakflag++;
                break;
            }
        }
        else if (expression[i] == ']')
        {
            if(arrPeek(&exp, &tmp) == EXIT_SUCCESS)
            {
                if(tmp == '[')
                {
                    arrPop(&exp, &tmp);
                }
                else
                {
                    sprintf(result, "Non valid expression!\n");
                    breakflag++;
                    break;
                }
            }
            else
            {
                sprintf(result, "Non valid expression!\n");
                breakflag++;
                break;
            }
        }
        else if (expression[i] == '}')
        {
            if(arrPeek(&exp, &tmp) == EXIT_SUCCESS)
            {
                if(tmp == '{')
                {
                    arrPop(&exp, &tmp);
                }
                else
                {
                    sprintf(result, "Non valid expression!\n");
                    breakflag++;
                    break;
                }
            }
            else
            {
                sprintf(result, "Non valid expression!\n");
                breakflag++;
                break;
            }
        }
    }
    if(!breakflag && exp.stackLen == 0)
        sprintf(result, "Valid expression!\n");
    else if (!breakflag)
        sprintf(result, "Non valid expression!\n");
    freeArr(&exp);

    clock_t end = clock();

    return (double)(end - start)/CLOCKS_PER_SEC;
}

double listCheck(char *expression, char *result)
{
    listStack_t exp;
    char tmp = 0, breakflag = 0;
    initList(&exp);

    clock_t start = clock();
    for(unsigned i = 0; i < strlen(expression); i++)
    {
        if(expression[i] == '(' || expression[i] == '[' || expression[i] == '{')
            listPush(&exp, (data_t*)&expression[i]);
        else if (expression[i] == ')')
        {
            if(listPeek(&exp, (data_t*)&tmp) == EXIT_SUCCESS)
            {
                if(tmp == '(')
                {
                    listPop(&exp, (data_t*)&tmp);
                }
                else
                {
                    sprintf(result, "Non valid expression!\n");
                    breakflag++;
                    break;
                }
            }
            else
            {
                sprintf(result, "Non valid expression!\n");
                breakflag++;
                break;
            }
        }
        else if (expression[i] == ']')
        {
            if(listPeek(&exp, (data_t*)&tmp) == EXIT_SUCCESS)
            {
                if(tmp == '[')
                {
                    listPop(&exp, (data_t*)&tmp);
                }
                else
                {
                    sprintf(result, "Non valid expression!\n");
                    breakflag++;
                    break;
                }
            }
            else
            {
                sprintf(result, "Non valid expression!\n");
                breakflag++;
                break;
            }
        }
        else if (expression[i] == '}')
        {
            if(listPeek(&exp, (data_t*)&tmp) == EXIT_SUCCESS)
            {
                if(tmp == '{')
                {
                    listPop(&exp, (data_t*)&tmp);
                }
                else
                {
                    sprintf(result, "Non valid expression!\n");
                    breakflag++;
                    break;
                }
            }
            else
            {
                sprintf(result, "Non valid expression!\n");
                breakflag++;
                break;
            }
        }
    }
    if(!breakflag && exp.stackLen == 0)
        sprintf(result, "Valid expression!\n");
    else if (!breakflag)
        sprintf(result, "Non valid expression!\n");
    freeList(&exp);

    clock_t end = clock();

    return (double)(end - start)/CLOCKS_PER_SEC;
}

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
            char expression[512];
                        
            printf("Input string with brackets('()' or '[]' or '{}') and without spacebars:");
            if(scanf("%511s", expression) != 1)
            {
                printf("Wrong Input!\n");
                break;
            }

            char result[50];

            double arr1000 = 0, arr5000 = 0,  arr10000 = 0;
            double list1000 = 0, list5000 = 0, list10000 = 0;

            for(int i = 0; i < 1000; i++)
            {
                arr1000 += arrCheck(expression, result);
                list1000 += listCheck(expression, result);
            }
            for(int i = 0; i < 5000; i++)
            {
                arr5000 += arrCheck(expression, result);
                list5000 += listCheck(expression, result);
            }
            for(int i = 0; i < 10000; i++)
            {
                arr10000 += arrCheck(expression, result);
                list10000 += listCheck(expression, result);
            }

            printf(" arr time : 1000 = %lf, 5000 = %lf, 10000 = %lf\n", arr1000, arr5000, arr10000);
            printf(" list time : 1000 = %lf, 5000 = %lf, 10000 = %lf\n", list1000, list5000, list10000);
            printf("%s", result);
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
            system("clear");
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
