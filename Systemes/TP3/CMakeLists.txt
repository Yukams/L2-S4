cmake_minimum_required(VERSION 3.17)
project(TP3 C)

set(CMAKE_C_STANDARD 11)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ..)

include_directories(.)

add_executable(Course_au_clavier
        Course_au_clavier.c
        term_canon.c
        term_canon.h)
