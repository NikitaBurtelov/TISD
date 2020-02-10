#include "headers/mazeGen.h"

/* >defines
#define VISITED 5
#define CELL 0
#define WALL 1
#define DISTANCE 2
*/

/* >includes
"data_t.h"
"stackListRoutines.h"
<math.h>
<stdio.h>
<stdlib.h>
<string.h>
<malloc.h>
<stdbool.h>
<time.h>
<unistd.h>
*/

/* >structure
typedef struct      // представление лабиринта
{                   // максимальный размер для вывода в консоль 99x99 символов; ширина == высота - только нечетные числа
    int width;      // ширина; координата y
    int height;      // высота; координата х
    int **map;    // двумерный массив
} maze;
*/

/* >structure
typedef struct cellString // массив клеток
{
    cell* cells;
    int size;
} cellString;
*/

//>documentation
/*!
 * \brief create_arr
 * \param p             // указатель на массив
 * \param len           // длина массива
 * \return              // EXIT_SUCCESS - массив успешно создан; EXIT_FAILURE - ошибка во время создания массива
 * создание динамического массива по указателю
 */
int create_arr(int **p, int len) //>signature
{
    *p = calloc((unsigned)len * sizeof (int), sizeof(int));

    if (!*p)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

void clear (void) //>signature
{
  if(!feof(stdin))
    while ( getchar() != '\n' );
}

//>documentation
/*!
 * \brief create_matrix
 * \param p             // указатель на матрицу
 * \param strings       // высота матрицы
 * \param columns       // ширина матрицы
 * создание матрицы по указателю
 * \return              // EXIT_SUCCESS - матрица успешно создана; EXIT_FAILURE - ошибка во время создания матрицы
 */
int create_matrix(int ***p, int strings, int columns) //>signature
{
    if (create_arr((int **)p, strings))
        return EXIT_FAILURE;
    for(int i = 0; i < strings; i++)
        if (create_arr(&((*p)[i]), columns))
            return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

//>documentation
/*!
 * \brief free_matrix
 * \param p             // указатель на матрицу
 * \param strings       // высота матрицы
 * \return
 * удаление матрицы по указателю
 */
void free_matrix(int ***p, int strings) //>signature
{
    for(int i = 0; i < strings; i++)
        free((*p)[i]);
    free(*p);
}


//>documentation
/*!
 * \brief mazeToFile
 * \param maze_t
 * экспортирует лабиринт в файл
 */
void mazeToFile(maze maze_t) //>signature
{
    FILE *fp;
    fp = fopen("genedLab.txt", "w");
    fprintf(fp, "%d\n", maze_t.width);
    for(int i = 0; i < maze_t.width; i++)
    {
        for(int j = 0; j < maze_t.width; j++)
        {
            fprintf(fp, "%d", maze_t.map[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);

}

//>documentation
/*!
 * \brief initCellString
 * \param string
 * \param len
 * выделяет память под массив клеток нужной длины
 */
void initCellString(cellString *string, int len) //>signature
{
    string->size = len;
    string->cells = (cell *)malloc(sizeof (cell) * (unsigned)len);
}

//>documentation
/*!
 * \brief printMaze
 * \param maze          // структура лабиринта
 * выводит на экран лабиринт
 */
void printMaze(maze maze) //>signature
{
    for(int i = 0; i < maze.height; i++)
    {
        for(int j = 0; j < maze.width; j++)
            if(maze.map[i][j] == CELL)
                //printf("%d", maze.map[i][j]);

                printf(" ");
            else if(maze.map[i][j] == VISITED)
                printf(" ");
            else
                printf("█");
        printf("\n");
    }
}

//>documentation
/*!
 * \brief createBorders
 * \param maze
 * создает внешние границы лабиринта вход, выход и сетку стен
 */
void createBorders(maze *maze) //>signature
{
    for(int i = 0; i < maze->height; i++)
        for(int j = 0; j < maze->width; j++)
            if(((i % 2 != 0) && (j % 2 != 0))                               // если позиция не четная по i и j
                    && ((i < maze->height - 1) && (j < maze->width - 1)))    // и лежит в границах лабиринта
                maze->map[i][j] = CELL;                                     // то это клетка
            else
                maze->map[i][j] = WALL;                                     // иначе это стена
}

//>documentation
/*!
 * \brief breakWall
 * \param maze
 * \param first
 * \param second
 * отмечает стенку между клетками cell и second как посещенную клетку
 */
void breakWall(maze *maze, cell first, cell second) //>signature
{
    int diffX = (int)first.x - (int)second.x;
    int diffY = (int)first.y - (int)second.y;

    cell wall = {first.x, first.y};

    if(diffX < 0 && diffY == 0)
        wall.x += 1;

    if(diffX > 0 && diffY == 0)
        wall.x -= 1;

    if(diffX == 0 && diffY > 0)
        wall.y -= 1;

    if(diffX == 0 && diffY < 0)
        wall.y += 1;

    maze->map[wall.x][wall.y] = VISITED;
}

//>documentation
/*!
 * \brief getNeighbours
 * \param maze
 * \param c
 * \return
 * возвращает массив соседних непосещенных клеток клетки
 */
cellString getNeighbours(maze maze, cell c) //>signature
{
    int i;
    int x = c.x;
    int y = c.y;
    cell up = {x, y - DISTANCE};
    cell dw = {x + DISTANCE, y};
    cell rt = {x, y + DISTANCE};
    cell lt = {x - DISTANCE, y};
    cell d[4]  = {dw, rt, up, lt};
    int size = 0;

    cellString cells;
    cells.cells = malloc(4 * sizeof(cell));

    for(i = 0; i < 4; i++) //для каждого направдения
    {
        if(d[i].x > 0 && d[i].x < maze.width && d[i].y > 0 && d[i].y < maze.height) //если не выходит за границы лабиринта
        {
            int mazeCellCurrent = maze.map[d[i].x][d[i].y];
            cell cellCurrent = d[i];
            if(mazeCellCurrent != WALL && mazeCellCurrent != VISITED) //и не посещена\является стеной
            {
                cells.cells[size] = cellCurrent; //записать в массив
                size++;
            }
        }
    }
    cells.size = size;
    return cells;
}

//>documentation
/*!
 * \brief unvisitedPoints
 * \param maze
 * \return
 * возвращает правду, если есть непосещенные точки
 * возвращает ложь, если непосещенных точек нет
 */
bool unvisitedPoints(maze maze) //>signature
{
    for(int i = 0; i < maze.height - 1; i++)
        for(int j = 0; j < maze.width - 1; j++)
            if(maze.map[i][j] == 0)
                return true;
    return false;
}

//>documentation
/*!
 * \brief randomRange
 * \param a
 * \param b
 * \return
 * возращает произвольное число из отрезка [a; b]
 */
int randomRange(int a, int b, clock_t seed) //>signature
{
    srand((unsigned)(time(NULL)* seed));
    return a +(rand() % (1 + b - a));
}

//>documentation
/*!
 * \brief getUnvisitedCells
 * \param maze
 * \return
 * возвращает массив непосещенных клеток лабиринта
 */
cellString getUnvisitedCells(maze maze) //>signature
{
    cellString cellString;
    initCellString(&cellString, maze.width*maze.height);
    for(int i = 0; i < maze.height; i++)
        for(int j = 0; j < maze.width; j++)
            if(maze.map[i][j] == CELL)
            {
                cell cell = {i, j};
                cellString.cells[i] = cell;
                cellString.size++;
            }
    return cellString;
}

//>documentation
/*!
 * \brief filllMaze
 * \param maze
 * непосредственно генерация лабиринта
 */
void fillMaze(maze *maze, int mode) //>signature
{
    createBorders(maze);

    srand((unsigned)time(NULL));
    clock_t seed = clock();

    listStack_t cellsStack;
    initList(&cellsStack);

    int beginX = 0;
    int beginY = 0;
    while(beginX % 2 == 0 || beginY % 2 == 0)
    {
        beginX = randomRange(1 , maze->width - 1, seed);
        beginY = randomRange(1 , maze->width - 1, seed);
    }
    cell currentCell = {beginX, beginY};

    listPush(&cellsStack, &currentCell);
    maze->map[currentCell.x][currentCell.y] = VISITED;
    int unvisitedCells = (maze->width/2)*(maze->width/2);

    do
    {
      cellString neighbours = getNeighbours(*maze, currentCell);            // Просмотр всех соседей текущей клетки

      if(neighbours.size != 0)              // если есть соседи (размер != 0)
      {
          cell nextCell;
          if(neighbours.size - 1 == 0)
               nextCell = neighbours.cells[0];
          else
          {
               seed = time(NULL) % clock();
               nextCell = neighbours.cells[randomRange(0, neighbours.size - 1, seed)];            // Задаем следующую клетку
          }
          listPeek(&cellsStack, &currentCell);          // смотрим верхнюю клетку в стеке
          breakWall(maze, nextCell, currentCell);           // заменяем стену клеткой между последней клеткой в стеке
                                                            // и выбранной клеткой, а также отмечаем получившуюся клетку как посещенную
          currentCell = nextCell;           // следующая клетка становится текущей
          listPush(&cellsStack, &currentCell);              // добавляем в стек текущую клетку
          maze->map[currentCell.x][currentCell.y] = VISITED;            // отмечаем текущую клетку как посещенную
          free(neighbours.cells);
          unvisitedCells--;
          if(mode == 1)
          {
              usleep(1e+6 * 0.01);
              system("clear");
              printf("\n");
              printMaze(*maze);
          }
      }
      else if(cellsStack.stackLen > 0)
          listPop(&cellsStack, &currentCell);
      else
      {
          seed = time(NULL) % clock();
          cellString cellStringUnvisited = getUnvisitedCells(*maze);
          int randNum = randomRange(0, cellStringUnvisited.size-1, seed);
          currentCell = cellStringUnvisited.cells[randNum];
          free(cellStringUnvisited.cells);
          unvisitedCells--;
      }
    } while(unvisitedPoints(*maze));

    for(int i = 1; i < maze->width-1; i++)
        for(int j = 1; j < maze->width-1 ; j++)
            if(maze->map[i][j] == VISITED)
                maze->map[i][j] = CELL;

    freeList(&cellsStack);
	system("clear");
	
	system("clear");
	printMaze(*maze);
}

// >documentation
/*!
 * \brief mazeFromFile
 * \param maze
 * импорт лабиринт из файла
 */
void mazeFromFile(maze *maze) //>signature
{
    FILE *fp;
   fp = fopen("genedLab.txt", "r");

   int side;
   fscanf(fp, "%d\n", &side);
   maze->width = maze->height = side;
   create_matrix(&maze->map, side, side);

   int rc;
   for(int i = 0; i < side; i++)
       for(int j = 0; j < side; j++)
       {
           do
           {
               rc = fscanf(fp, "%1d", &(maze->map[i][j]));
           }
           while(rc != 1 && rc != EOF);
       }
}

