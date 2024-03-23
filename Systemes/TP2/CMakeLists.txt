cmake_minimum_required(VERSION 3.17)
project(TP2 C)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../Matrice)

set(CMAKE_C_STANDARD 11)

include_directories(Matrice)

add_executable(exo3_V2
        Matrice/exo3_V2.c
        Matrice/matrice.c
        Matrice/matrice.h
        Matrice/traiterLigne.c
        Matrice/traiterLigne.h)