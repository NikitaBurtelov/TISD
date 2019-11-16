#ifndef LAB_04_OUTPUT_H
#define LAB_04_OUTPUT_H

#include "what.h"
#include "maze.h"

void print_struct_mass(Mass_double p, Mass_int s, int type_field);

void print_struct_list_int(const List_int *head);

void print_struct_list_str(const List_str *head);

void print_struct_mass_str(Mass_str s);

void print_struct_maze(List_maze *head, MAZE_ONE);

void print_maze(MAZE_ONE);

#endif //LAB_04_OUTPUT_H
