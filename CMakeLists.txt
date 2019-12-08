cmake_minimum_required(VERSION 3.10.2)
project(sudoku_solver)
include_directories(include)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

add_custom_command(OUTPUT git_commit.h COMMAND 
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/get_git_commit.sh 
    ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/.git/index )
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(common STATIC src/common.cpp git_commit.h)
target_compile_features(common PUBLIC cxx_std_17)

add_library(algo1 STATIC src/algorithm1.cpp git_commit.h)
target_compile_features(algo1 PUBLIC cxx_std_17)

add_library(algo2 STATIC src/algorithm2.cpp git_commit.h)
target_compile_features(algo2 PUBLIC cxx_std_17)

add_executable(sudoku_solver src/main.cpp git_commit.h)
target_link_libraries(sudoku_solver common algo2)

