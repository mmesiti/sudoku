cmake_minimum_required(VERSION 3.10.2)
project(sudoku_solver)
include_directories(include)

enable_testing()
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

file(GLOB SOURCES "src/*.cpp")

add_executable(sudoku_solver src/main/main.cpp ${SOURCES})

add_subdirectory(tests)


