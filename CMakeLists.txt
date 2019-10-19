cmake_minimum_required(VERSION 3.10.2)
project(sudoku_solver)
include_directories(include)

enable_testing()
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )


add_library(board STATIC src/board.cpp)
target_compile_features(board PUBLIC cxx_std_17)

add_executable(sudoku_solver src/main/main.cpp )
target_link_libraries(sudoku_solver board)

add_subdirectory(tests)


