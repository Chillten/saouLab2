cmake_minimum_required(VERSION 3.5)
project(saouLab2)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES src/main.c src/bstree.c src/bstree.h src/hashtab.c src/hashtab.h src/get_time.h)
add_executable(saouLab2 ${SOURCE_FILES})