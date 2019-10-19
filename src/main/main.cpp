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

  auto t_end = sudoku::heuristics2(t);
  std::cout << "End - heuristics2:" << std::endl;
  if(t_end) std::cout << *t_end;
  else {
      std::cout << "Failed." << std::endl;
      return 1;
  }

  return 0;
}
