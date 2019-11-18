cmake_minimum_required(VERSION 3.15)
project(lab_05 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab_05 main.c headers/header.h headers/push.h headers/insert.h headers/delete.h headers/output.h output.c insert.c init.c push.c delete.c)