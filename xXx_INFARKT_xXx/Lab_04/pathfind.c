#include "headers/pathfind.h"

/* >includes
"data_t.h"
"mazeGen.h"
"stackListRoutines.h"
"stackArrRoutines.h"
*/

cellString getPathNeighbours(maze maze, cell c) //>signature
{
    int i;
    int x = c.x;
    int y = c.y;
    cell up = {x, y - 1};
    cell dw = {x + 1, y};
    cell rt = {x, y + 1};
    cell lt = {x - 1, y};
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

int listFindPath(maze maze) //>signature
{
    listStack_t cellsStack;
    initList(&cellsStack);

    clock_t seed = clock();

    cell currentCell = {1, 1};
    cell finalCell = {maze.width - 2, maze.width - 2};

    while((currentCell.x != finalCell.x) || (currentCell.y != finalCell.y))
    {
        cellString neighbours = getPathNeighbours(maze, currentCell);

        if(neighbours.size != 0) // если текущая клетка имеет непосещенных соседей
        {
            maze.map[currentCell.x][currentCell.y] = VISITED;
            listPush(&cellsStack, &currentCell); // положить текущую в стек

            cell nextCell;
            if(neighbours.size - 1 == 0) // выбрать случайного соседа и отметить как новую клетк
                 nextCell = neighbours.cells[0];
            else
            {
                 seed = time(NULL) % clock();
                 nextCell = neighbours.cells[randomRange(0, neighbours.size - 1, seed)];
            }

            currentCell = nextCell; // сделать новую клетку текущей и отметить как посещенную
            maze.map[currentCell.x][currentCell.y] = VISITED;

        }
        else if(cellsStack.stackLen != 0) // иначе если стек не пуст и посещенных соседей нет
        {
            listPop(&cellsStack, &currentCell); // взять клетку из стека и сделать ее текущей
        }
        else // иначе пути не существует
        {
            printf("There is no path throw maze!\n");
            return EXIT_FAILURE;
        }
    }

    cellString path;
    path.cells = malloc(sizeof (cell) * (unsigned)cellsStack.stackLen);
    path.size = cellsStack.stackLen;
    for(int i = cellsStack.stackLen - 1; i >= 0; i--)
        listPop(&cellsStack, &path.cells[i]);

    printf("Your path is: \n");
    for(int i = 1; i < path.size+1; i++)
    {
        printf("(%2d,%2d) ", path.cells[i-1].x, path.cells[i-1].y);
        if(i%10 == 0)
            printf("\n");
    }
    printf("(%d,%d)", finalCell.x, finalCell.y);
    printf("\n");

    free(path.cells);
    freeList(&cellsStack);

    return EXIT_SUCCESS;

}

int arrFindPath(maze maze) //>signature
{
    arrStack_t cellsStack;
    initArr(&cellsStack, sizeof (cell));

    clock_t seed = clock();

    cell currentCell = {1, 1};
    cell finalCell = {maze.width - 2, maze.width - 2};

    while((currentCell.x != finalCell.x) || (currentCell.y != finalCell.y))
    {
        cellString neighbours = getPathNeighbours(maze, currentCell);

        if(neighbours.size != 0) // если текущая клетка имеет непосещенных соседей
        {
            maze.map[currentCell.x][currentCell.y] = VISITED;
            arrPush(&cellsStack, &currentCell); // положить текущую в стек

            cell nextCell;
            if(neighbours.size - 1 == 0) // выбрать случайного соседа и отметить как новую клетк
                 nextCell = neighbours.cells[0];
            else
            {
                 seed = time(NULL) % clock();
                 nextCell = neighbours.cells[randomRange(0, neighbours.size - 1, seed)];
            }

            currentCell = nextCell; // сделать новую клетку текущей и отметить как посещенную
            maze.map[currentCell.x][currentCell.y] = VISITED;

        }
        else if(cellsStack.stackLen != 0) // иначе если стек не пуст и посещенных соседей нет
        {
            arrPop(&cellsStack, &currentCell); // взять клетку из стека и сделать ее текущей
        }
        else // иначе пути не существует
        {
            printf("There is no path throw maze!\n");
            return EXIT_FAILURE;
        }
    }

    cellString path;
    path.cells = malloc(sizeof (cell) * (unsigned)cellsStack.stackLen);
    path.size = cellsStack.stackLen;
    for(int i = cellsStack.stackLen - 1; i >= 0; i--)
        arrPop(&cellsStack, &path.cells[i]);

    printf("Your path is: \n");
    for(int i = 0; i < path.size; i++)
    {
        printf("(%-2d,%2d)", path.cells[i].x, path.cells[i].y);
        if(i%10 == 0 && i != 0)
            printf("\n");
    }
    printf("(%d,%d)", finalCell.x, finalCell.y);
    printf("\n");

    free(path.cells);
    freeArr(&cellsStack);

    return EXIT_SUCCESS;

}
