#ifndef LAB_04_MAZE_H
#define LAB_04_MAZE_H

#define LEN_ONE 10 // размер лабиринта #1

#define LEN_SEC 4  // размер лабиринта #2
#define BLOCK -1 // пути нет
#define LOCK_FLAG 1 // есть развилка
#define FIN_X 3
#define FIN_Y 3
#define FINISH 10
//массив тупиков
typedef int LOCK[LEN_SEC*LEN_SEC][2];
//массив развилок
typedef short FORK[LEN_SEC*LEN_SEC][2];
//Maze_map
typedef short MAZE_ONE[LEN_SEC][LEN_SEC];
//Maze_struct
typedef struct List_tag_maze
{
    short step; //1 - up, 3- down, 2 - right, 3 - left
    short count_lock; //развилки
    short count_fork; //тупики
    struct List_tag_maze *next;
}List_maze;

void init_maze_one(MAZE_ONE maze);

void init_fork(FORK fork_maze);

void init_lock(LOCK lock_maze);

int init_ls_maze(List_maze **head);

int push_ls_maze(List_maze **head);

int lock_coord(MAZE_ONE maze, List_maze **head, int x, int y);

int search(FORK lock_mass, int x, int y);

short where_to_go(MAZE_ONE maze, List_maze **head, LOCK lock_mass, FORK fork_maze, const int x, const int y, short *);

int back(MAZE_ONE maze, List_maze **head, int *x, int *y, LOCK lock_maze, FORK fork_maze);

int finish_f(int x, int y);

int movement();

#endif //LAB_04_MAZE_H
