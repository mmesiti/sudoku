cmake_minimum_required(VERSION 3.10.2)
project(sudoku_solver)
include_directories(include)

enable_testing()
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )


add_library(libcommon STATIC src/common.cpp)
target_compile_features(libcommon PUBLIC cxx_std_17)

add_library(libalgo1 STATIC src/algorithm1.cpp)
target_compile_features(libalgo1 PUBLIC cxx_std_17)

add_library(libalgo2 STATIC src/algorithm2.cpp)
target_compile_features(libalgo2 PUBLIC cxx_std_17)

add_executable(sudoku_solver src/main/main.cpp )
target_link_libraries(sudoku_solver libcommon libalgo2)

add_subdirectory(tests)


