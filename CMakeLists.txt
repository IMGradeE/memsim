cmake_minimum_required(VERSION 3.22)
project(Challenge6 C)

set(CMAKE_C_STANDARD 23)

add_library(Challenge6 SHARED library.c
        simulator.c
)
