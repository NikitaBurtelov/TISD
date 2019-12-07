cmake_minimum_required(VERSION 3.15)
project(lab_08_2 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab_08_2 main.c array_routines.c my_math.c headers/array_routines.h headers/includes.h headers/my_math.h)