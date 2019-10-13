cmake_minimum_required(VERSION 3.15.2)

project(sudoku_solver)
include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(sudoku_solver ${SOURCES})
