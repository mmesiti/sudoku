cmake_minimum_required(VERSION 3.10.2)
project(sudoku_solver)
include_directories(include)

enable_testing()
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )


add_library(common STATIC src/common.cpp)
target_compile_features(common PUBLIC cxx_std_17)

add_library(algo1 STATIC src/algorithm1.cpp)
target_compile_features(algo1 PUBLIC cxx_std_17)

add_library(algo2 STATIC src/algorithm2.cpp)
target_compile_features(algo2 PUBLIC cxx_std_17)

add_executable(sudoku_solver src/main/main.cpp )
target_link_libraries(sudoku_solver common algo2)

add_subdirectory(tests)


