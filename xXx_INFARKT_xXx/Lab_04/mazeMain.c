#include "headers/mazeGen.h"
#include "headers/stackListRoutines.h"
#include "headers/pathfind.h"

int main(void)
{
    maze maze;

    char choose;
    printf("Input size of labyrynth side (non even number x, where 99>=x>=5): ");
    if((scanf("%d", &maze.width) != 1) || (maze.width % 2 == 0) || (maze.width < 5) || (maze.width > 99))
    {
        clear();
        printf("Wrong input!\n");
        getchar();
        return EXIT_FAILURE;
    }
    else
    {
        maze.height = maze.width;
        create_matrix(&maze.map, maze.width, maze.width);
    }
    clear();

    printf("Enable runtime drawing?y/n\n");
    scanf("%c", &choose);
    clear();
    if(choose == 'y')
        choose = 1;
    else if(choose == 'n')
        choose = 0;
    else
    {
        printf("Wrong input!\n");
        getchar();
        return EXIT_FAILURE;
    }

    system("clear");
    fillMaze(&maze, choose);
    if(choose == 0)
        printMaze(maze);

    mazeToFile(maze);

    listFindPath(maze);

    free_matrix(&maze.map, maze.width);

    getchar();
    return EXIT_SUCCESS;
}
