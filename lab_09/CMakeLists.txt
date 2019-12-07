cmake_minimum_required(VERSION 3.15)
project(lab_09 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab_09 main.c math.c matrix_routines.c headers/includes.h headers/math.h headers/matrix_routines.h headers/types.h)