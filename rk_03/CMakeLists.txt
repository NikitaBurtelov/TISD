cmake_minimum_required(VERSION 3.15)
project(rk_03 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(rk_03
        functins.h
        functions.c
        main.c)
