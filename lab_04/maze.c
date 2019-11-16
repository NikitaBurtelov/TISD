#include "headers/maze.h"
#include "headers/what.h"
#include "headers/output.h"

void init_maze_one(MAZE_ONE maze)
{
    // 0 - block, 1 - pass
    // Вход 0.0 , Выход 4.4
    //1 - up, 3- down, 0 - right, 4 - left
    short maze_loc[LEN_SEC][LEN_SEC] =
            {
            {1,0,1,0},
            {1,1,1,0},
            {1,0,1,1},
            {1,1,0,1}
            };

    for (int i = 0; i < LEN_SEC; i++)
    {
        for (int j = 0; j < LEN_SEC; j++)
        {
            maze[i][j] = maze_loc[i][j];
        }
    }
}

int push_ls_maze(List_maze **head)
{
    List_maze *tmp = malloc(sizeof(List_maze));
    int count_fork = 0;

    if (tmp == NULL)
    {
        return EXIT_FAILURE;
    }
    tmp->count_fork = (*head)->count_fork;
    tmp->next = *head;

    *head = tmp;
    (*head)->count_fork = tmp->count_fork;

    return EXIT_SUCCESS;
}

int init_ls_maze(List_maze **head)
{
    List_maze *tmp = malloc(sizeof(List_maze));
    int count_fork = 0;

    if (tmp == NULL)
    {
        return EXIT_FAILURE;
    }
    tmp->count_fork = 0;
    tmp->next = *head;

    *head = tmp;
    (*head)->count_fork = tmp->count_fork;

    return EXIT_SUCCESS;
}

void init_fork(FORK fork_maze)
{
    for (int i = 0; i < LEN_SEC * LEN_SEC; i++)
    {
        fork_maze[i][0] = -1;
        fork_maze[i][1] = -1;
    }
}

void init_lock(LOCK lock_maze)
{
    for (int i = 0; i < LEN_SEC * LEN_SEC; i++)
    {
        lock_maze[i][0] = -1;
        lock_maze[i][1] = -1;
    }
}

//проверка на развилку
int lock_coord(MAZE_ONE maze, List_maze **head, int x, int y)
{
    short count = 0;
    //1 - up, 3- down, 0 - right, 4 - left
    if (x != 0)
    {
        if (maze[x - 1][y] == 1 && (*head)->step != 3)
            count++;
    }
    if (x != LEN_SEC - 1)
    {
        if (maze[x + 1][y] == 1 && (*head)->step != 1)
            count++;
    }
    if (y != 0)
    {
        if (maze[x][y - 1] == 1 && (*head)->step != 0)
            count++;
    }
    if (y != LEN_SEC  - 1)
    {
        if (maze[x][y + 1] == 1 && (*head)->step != 4)
            count++;
    }
    //Условие развилки: count >= 2
    if (count >= 2)
        return LOCK_FLAG;

    return EXIT_SUCCESS;
}

int search(FORK lock_mass, int x, int y)
{
    //0 - тупик, 1 - путь есть
    for (int i = 0; i < LEN_SEC; i++)
    {
        if (x == lock_mass[i][0] && y == lock_mass[i][1])
            return 0;
    }
    return 1;
}

short where_to_go(MAZE_ONE maze, List_maze **head, LOCK lock_mass, FORK fork_maze, const int x, const int y, short *len_lock)
{
    // x - строка, y - столбец
    //1 - up, 3- down, 0 - right, 4 - left
    short turn;

    if (finish_f(x, y) == FINISH)
        return FINISH;

    //Если это развилка
    if (lock_coord(maze, head, x, y) == LOCK_FLAG)
    {
        (*head)->count_lock = *len_lock;
        lock_mass[(*head)->count_lock][0] = x;
        lock_mass[(*head)->count_lock][1] = y;
        (*len_lock)++;
    }
    (*head)->count_lock = *len_lock;
    //необходима отдельная проверка граничных столбцов и строк
    if (x == 0)
    {
        if (y == 0)
        {
            if (maze[1][0] == 1 && (*head)->step == 4 && search(fork_maze, 1, y) == 1)
                return 3;
            else if (maze[0][1] == 1 && (*head)->step == 1 && search(fork_maze, x, 1))
                return 0;
        }
        else if (y == LEN_SEC - 1)
        {
            if (maze[1][y] == 1 && (*head)->step == 4 && search(fork_maze, 1, y))
                return 3;
            else if (maze[x][LEN_SEC - 2] == 1 && (*head)->step == 1 && search(fork_maze, x, LEN_SEC - 2))
                return 4;
        }
    }
    else if (x == LEN_SEC - 1)
    {
        if (y == 0)
        {
            if (maze[LEN_SEC - 2][y] == 1 && (*head)->step == 4 && search(fork_maze, LEN_SEC - 2, y))
                return 1;
            else if (maze[LEN_SEC - 1][y + 1] == 1 && (*head)->step == 3 && search(fork_maze, LEN_SEC - 1, y + 1))
                return 0;
        }
        else if (y == LEN_SEC - 1)
        {
            if (maze[LEN_SEC - 2][y] == 1 && (*head)->step == 0 && search(fork_maze, LEN_SEC - 2, y))
                return 1;
            else if (maze[LEN_SEC - 1][LEN_SEC - 2] == 1 && (*head)->step == 3 && search(fork_maze, LEN_SEC - 1, LEN_SEC - 2))
                return 4;
        }
    }
    // строка 0, кроме боковых
    if (x == 0 && y != 0 && y != LEN_SEC - 1)
    {
        //--->
        if (maze[x][y + 1] == 1 && ((*head)->step == 0 || (*head)->step == 1) && search(fork_maze, x, y + 1))
            return 0;
        else if (maze[x + 1][y] == 1 && (*head)->step == 0 && search(fork_maze, x + 1, y))
            return 3;
        else if (maze[x + 1][y] == 1 && (*head)->step == 4 && search(fork_maze, x + 1, y))
            return 3;
        else if (maze[x][y - 1] == 1 && ((*head)->step == 4 || (*head)->step == 1) && search(fork_maze, x, y - 1))
           return 4;

    }
    if (x == LEN_SEC - 1 && y != 0 && y != LEN_SEC - 1)
    {
        if (maze[x][y + 1] == 1 && ((*head)->step == 0 || (*head)->step == 3) && search(fork_maze, x, y + 1))
            return 0;
        else if (maze[x + 1][y] == 1 && (*head)->step == 0 && search(fork_maze, x + 1, y))
            return 1;
        else if (maze[x + 1][y] == 1 && (*head)->step == 4 && search(fork_maze, x + 1, y))
            return 1;
        else if (maze[x][y - 1] == 1 && ((*head)->step == 4 || (*head)->step == 3) && search(fork_maze, x, y - 1))
            return 4;
    }
    //боковые столбцы
    if (y == 0 && x != 0 && x != LEN_SEC -1)
    {
        //1 - up, 3- down, 0 - right, 4 - left
        if (maze[x][y + 1] && (*head)->step == 1 && search(fork_maze, x, y + 1))
            return 0;
        else if (maze[x - 1][y] && ((*head)->step == 1 || (*head)->step == 4) && search(fork_maze, x - 1, y))
            return 1;
        else if (maze[x + 1][y] && ((*head)->step == 3 || (*head)->step == 4) && search(fork_maze, x + 1, y))
            return 3;
        else if (maze[x][y + 1] && (*head)->step == 3 && search(fork_maze, x, y + 1))
            return 0;
    }

    if (y == LEN_SEC - 1 && x != 0 && x != LEN_SEC - 1)
    {
        if (maze[x][y - 1] && (*head)->step == 1 && search(fork_maze, x, y - 1))
            return 4;
        else if (maze[x - 1][y] && ((*head)->step == 1 || (*head)->step == 0) && search(fork_maze, x - 1, y))
            return 1;
        else if (maze[x + 1][y] && ((*head)->step == 3 || (*head)->step == 0) && search(fork_maze, x + 1, y))
            return 3;
        else if (maze[x][y - 1] && (*head)->step == 3 && search(fork_maze, x, y - 1))
            return 4;
    }
    //Основной путь
    if (y != LEN_SEC - 1 && y != 0 && x != 0 && x != LEN_SEC - 1)
    {
        //вниз
        if (maze[x][y + 1] && (*head)->step == 1 && search(fork_maze, x, y + 1))
            return 0;
        else if (maze[x - 1][y] && (*head)->step == 1 && search(fork_maze, x - 1, y))
            return 1;
        else if (maze[x][y - 1] && (*head)->step == 1 && search(fork_maze, x, y - 1))
            return 4;
        //вверх
        if (maze[x][y + 1] && (*head)->step == 3 && search(fork_maze, x, y + 1))
            return 0;
        else if (maze[x + 1][y] && (*head)->step == 3 && search(fork_maze, x + 1, y))
            return 3;
        else if (maze[x][y - 1] && (*head)->step == 3 && search(fork_maze, x, y - 1))
            return 4;
        //right
        if (maze[x][y + 1] && (*head)->step == 0 && search(fork_maze, x, y + 1))
            return 0;
        else if (maze[x + 1][y] && (*head)->step == 0 && search(fork_maze, x + 1, y))
            return 3;
        else if (maze[x - 1][y] && (*head)->step == 0 && search(fork_maze, x - 1, y))
            return 1;
        //left
        if (maze[x + 1][y] && (*head)->step == 4 && search(fork_maze, x + 1, y))
            return 3;
        else if (maze[x - 1][y] && (*head)->step == 4 && search(fork_maze, x - 1, y))
            return 1;
        else if (maze[x][y - 1] && (*head)->step == 4 && search(fork_maze, x, y - 1))
            return 4;
    }
    return BLOCK; //тупик ???.... YES
}

int back(MAZE_ONE maze, List_maze **head, int *x, int *y, LOCK lock_maze, FORK fork_maze)
{
    // необходимо вернуться именно на развилку
    //1 - up, 3- down, 0 - right, 4 - left
    void *pointer;
    int x_fork = lock_maze[(*head)->count_lock - 1][0];
    int y_fork = lock_maze[(*head)->count_lock - 1][1];

    while ((*x != x_fork) || (*y != y_fork))
    {
        pointer = *head;

        if ((*head)->step == 0)
            (*y)--;
        else if ((*head)->step == 4)
            (*y)++;
        else if ((*head)->step == 1)
            (*x)++;
        else if ((*head)->step == 3)
            (*x)--;

        *head = (*head)->next;
        free(pointer);
    }

    lock_maze[(*head)->count_lock - 1][0] = -1;
    lock_maze[(*head)->count_lock - 1][1] = -1;

    (*head)->count_lock--;

    fork_maze[(*head)->count_fork][0] = (short) *x;
    fork_maze[(*head)->count_fork][1] = (short) *y;

    if ((*head)->step == 0)
        fork_maze[(*head)->count_fork][1]++;
    else if ((*head)->step == 4)
        fork_maze[(*head)->count_fork][1]--;
    else if ((*head)->step == 1)
        fork_maze[(*head)->count_fork][0]--;
    else if ((*head)->step == 3)
        fork_maze[(*head)->count_fork][0]++;

    (*head)->count_fork--;

    return EXIT_FAILURE;
}

int finish_f(int x, int y)
{
    if (x == FIN_X && y == FIN_Y)
        return FINISH;

    return 0;
}

int movement()
{
    int x = 0, y = 0;
    short lock_len = 0, count = 1;
    int finish = 1, block = 1;

    int flag_finish = 1, flag_block = 1;
    short way;

    FORK fork_maze;
    LOCK lock_mass;
    List_maze *frst = NULL;
    MAZE_ONE maze;


    init_ls_maze(&frst);
    //создаем лабиринт
    init_maze_one(maze);
    push_ls_maze(&frst);
    init_fork(fork_maze);
    init_lock(lock_mass);
    //Куда идти ?

    //В конце тупик ?
    x = 0;
    y = 0;
    frst->count_lock = 0;
    frst->step = 4;
    frst->count_fork = 0;
    lock_len = 0;
    //Пока не дошли до конца
    while(flag_finish)
    {
        //пока нет тупика или нет поворота
        while (flag_block)
        {
            //1 - up, 3- down, 0 - right, 4 - left

            way = where_to_go(maze, &frst, lock_mass, fork_maze, x, y, &lock_len);
            push_ls_maze(&frst);
            (*frst).step = way;
            (*frst).count_lock = lock_len;
            if (way == 1)
                x--;
            else if (way == 3)
                x++;
            else if (way == 0)
                y++;
            else if (way == 4)
                y--;
            else if (way == FINISH)
            {
                flag_finish = 0;
                flag_block = 0;
                break;
            }
            else if (way == BLOCK)
            {
                flag_block = 0;
            }
        }
        //возвращаемся к последней развилке
        if (flag_finish != 0)
        {
            (*frst).step = way;
            (*frst).count_lock = lock_len;
            back(maze, &frst, &x, &y, lock_mass, fork_maze);
        }
        flag_block = 1;
    }

    printf("\nFinish\n");
    print_struct_maze(frst, maze);

    return EXIT_SUCCESS;
}