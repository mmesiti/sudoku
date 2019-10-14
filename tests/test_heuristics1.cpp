#include "board.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char **argv) {

  if (argc < 3) {
    std::cout << "Pass the file name as the first argument" << std::endl;
    std::cout << "And the expected output file as the second" << std::endl;
    return 1;
  }

  using sudoku::operator>>;
  using sudoku::operator<<;

  sudoku::Table t = sudoku::read_board(argv[1]);
  std::cout << "Start:" << std::endl;
  std::cout << t;
  sudoku::Table t_end_read = sudoku::read_board(argv[2]);
  std::cout << "End - reference:" << std::endl;
  std::cout << t_end_read;

  sudoku::Table t_end = sudoku::heuristics1(t);
  std::cout << "End - heuristics1:" << std::endl;
  std::cout << t_end;

  if (t_end != t_end_read)
    return 1;
  else
    return 0;
}