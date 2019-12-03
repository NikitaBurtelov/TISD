/*
This header file was generated automaticaly!
Generated at: 03 December 2019 (03.12.2019) At: 14:51:28
Amount of functions        : 15
Amount of documentated     : 14
All functions documentated : False
Amount of structures       : 2
Amount of enums            : 0
Function's names: 
   1 > breakWall
   2 > clear
   3 > createBorders
   4 > create_arr
   5 > create_matrix
   6 > fillMaze
   7 > free_matrix
   8 > getNeighbours
   9 > getUnvisitedCells
  10 > initCellString
  11 > mazeFromFile
  12 > mazeToFile
  13 > printMaze
  14 > randomRange
  15 > unvisitedPoints

*/

#ifndef __MAZEGEN_H__
#define __MAZEGEN_H__

#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "stackListRoutines.h"
#include "data_t.h"

#define VISITED 5
#define CELL 0
#define WALL 1
#define DISTANCE 2


typedef struct      // представление лабиринта
{                   // максимальный размер для вывода в консоль 99x99 символов; ширина == высота - только нечетные числа
    int width;      // ширина; координата y
    int height;      // высота; координата х
    int **map;    // двумерный массив
} maze;

typedef struct cellString // массив клеток
{
    cell* cells;
    int size;
} cellString;

/*!
* \brief create_arr
* \param p             // указатель на массив
* \param len           // длина массива
* \return              // EXIT_SUCCESS - массив успешно создан; EXIT_FAILURE - ошибка во время создания массива
* создание динамического массива по указателю
*/
int create_arr(int **p, int len);

void clear (void);

/*!
* \brief create_matrix
* \param p             // указатель на матрицу
* \param strings       // высота матрицы
* \param columns       // ширина матрицы
* создание матрицы по указателю
* \return              // EXIT_SUCCESS - матрица успешно создана; EXIT_FAILURE - ошибка во время создания матрицы
*/
int create_matrix(int ***p, int strings, int columns);

/*!
* \brief free_matrix
* \param p             // указатель на матрицу
* \param strings       // высота матрицы
* \return
* удаление матрицы по указателю
*/
void free_matrix(int ***p, int strings);

/*!
* \brief mazeToFile
* \param maze_t
* экспортирует лабиринт в файл
*/
void mazeToFile(maze maze_t);

/*!
* \brief initCellString
* \param string
* \param len
* выделяет память под массив клеток нужной длины
*/
void initCellString(cellString *string, int len);

/*!
* \brief printMaze
* \param maze          // структура лабиринта
* выводит на экран лабиринт
*/
void printMaze(maze maze);

/*!
* \brief createBorders
* \param maze
* создает внешние границы лабиринта вход, выход и сетку стен
*/
void createBorders(maze *maze);

/*!
* \brief breakWall
* \param maze
* \param first
* \param second
* отмечает стенку между клетками cell и second как посещенную клетку
*/
void breakWall(maze *maze, cell first, cell second);

/*!
* \brief getNeighbours
* \param maze
* \param c
* \return
* возвращает массив соседних непосещенных клеток клетки
*/
cellString getNeighbours(maze maze, cell c);

/*!
* \brief unvisitedPoints
* \param maze
* \return
* возвращает правду, если есть непосещенные точки
* возвращает ложь, если непосещенных точек нет
*/
bool unvisitedPoints(maze maze);

/*!
* \brief randomRange
* \param a
* \param b
* \return
* возращает произвольное число из отрезка [a; b]
*/
int randomRange(int a, int b, clock_t seed);

/*!
* \brief getUnvisitedCells
* \param maze
* \return
* возвращает массив непосещенных клеток лабиринта
*/
cellString getUnvisitedCells(maze maze);

/*!
* \brief filllMaze
* \param maze
* непосредственно генерация лабиринта
*/
void fillMaze(maze *maze, int mode);

/*!
* \brief mazeFromFile
* \param maze
* импорт лабиринт из файла
*/
void mazeFromFile(maze *maze);

#endif // __MAZEGEN_H__

