#include "board.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char **argv) {

  if (argc < 2) {
    std::cout << "Pass the file name as the first argument.";
    return 1;
  }

  using sudoku::operator>>;
  using sudoku::operator<<;

  sudoku::Table t = sudoku::read_board(argv[1]);
  std::cout << "Start:" << std::endl;
  std::cout << t;

  sudoku::Table t_end = sudoku::heuristics1(t);
  std::cout << "End - heuristics1:" << std::endl;
  std::cout << t_end;

  return 0;
}
