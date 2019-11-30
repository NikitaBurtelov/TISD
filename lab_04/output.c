#include "headers/output.h"
#include "headers/maze.h"
#include <locale.h>

void print_struct_mass(Mass_double p, Mass_int s, int type_mass)
{
    if (type_mass == 0)
        for (int i = 0; i <= p.top; i++)
            printf("\n%p: %lf", &p.elem[i], p.elem[i]);
    else
    {
        for (int i = 0; i <= s.top; i++)
            printf("\n%p: %d", &p.elem[i], s.elem[i]);
    }
}

void print_struct_mass_str(Mass_str s)
{
    for (int i = 0; i < s.top; i++)
        printf("\n%p: %c", &s.elem[i], s.elem[i]);
}

void print_struct_list_int(const List_int *head)
{
    int count = 0;
    while(head)
    {
        printf("\n%p: %d\n",head->next, head->value);
        head = head->next;
        count++;
    }
}

void print_struct_list_str(const List_str *head)
{
    int count = 0;
    if (head->next == NULL)
    {
        printf("Empty");
    }
    else {
        while (head)
        {
            printf("\n%p: %c\n", head->next, head->value);

            head = head->next;

            if (head->value == '\n')
                break;
            count++;
        }
    }
}

void print_maze(MAZE_ONE maze)
{
    for(int i = 0; i < LEN_SEC; i++)
    {
        if (i == 0)
        {
            printf("\n");
            for (int c = 0; c < LEN_SEC + 2; c++)
                printf("_");
            printf("\n");
        }
        for (int j = 0; j < LEN_SEC; j++)
        {
            if (j == 0)
                printf("|");

            if (maze[i][j] == 0)
                printf("|");
            else if (maze[i][j] == 10)
                printf("*");
            else
                printf(" ");

            if (j == LEN_SEC - 1)
                printf("|");
        }

        if (i == LEN_SEC - 1)
        {
            printf("\n");
            for (int c = 0; c < LEN_SEC + 2; c++)
                printf("_");
            printf("\n");
        }
        else
            printf("\n");
    }
}

void print_struct_maze(List_maze *head, MAZE_ONE maze)
{
    int arr[BUF_LEN];
    int count = 0, turn = 0, x = 0, y =0;

    setlocale(LC_ALL, NULL);

    while(head)
    {
        arr[count] = head->step;
        count++;
        head = head->next;
    }

    for(int i = 0,  j = count - 1; i < j; ++i, --j) {

        turn = arr[i];
        arr[i] = arr[j];
        arr[j] = turn;
    }
    printf("\n");
    for (int i = 1; i < count; i++)
    {
        if (arr[i] == 1)
            printf("%d. Up\n", i);
        else if (arr[i] == 3)
            printf("%d. Down\n", i);
        else if (arr[i] == 0)
            printf("%d. Right\n", i);
        else if (arr[i] == 4)
            printf("%d. Left\n", i);
        else if (arr[i] == 10)
            printf("END\n");
    }

    /*
    //1 - up, 3- down, 0 - right, 4 - left
    for (int j = 1; j < count; j ++)
    {
        printf("\n!!!!!!!!!!!!! %d\n", arr[j]);

        maze[x][y] = 10;

        if (arr[j] == 1)
            x--;
        else if (arr[j] == 3)
            x++;
        else if (arr[j] == 0)
            y++;
        else if (arr[j] == 4)
            y--;
        print_maze(maze);
    }
    */
}
