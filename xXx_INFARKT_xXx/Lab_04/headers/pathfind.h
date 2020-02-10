/*
This header file was generated automaticaly!
Generated at: 14 November 2019 (14.11.2019) At: 01:22:26
Amount of functions        : 3
Amount of documentated     : 0
All functions documentated : False
Amount of structures       : 0
Amount of enums            : 0
Function's names: 
   1 > arrFindPath
   2 > getPathNeighbours
   3 > listFindPath

*/

#ifndef __PATHFIND_H__
#define __PATHFIND_H__

#include "stackListRoutines.h"
#include "stackArrRoutines.h"
#include "mazeGen.h"
#include "data_t.h"

cellString getPathNeighbours(maze maze, cell c);

int listFindPath(maze maze);

int arrFindPath(maze maze);

#endif // __PATHFIND_H__

