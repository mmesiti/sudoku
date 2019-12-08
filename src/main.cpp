#include "common.hpp"
#include "algorithm2.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include "git_commit.h"

int main(int argc, char **argv) {

  std::cout << "Sudoku solver, commit " << GITCOMMIT << std::endl;

  if (argc < 2) {
    std::cout << "Pass the file name as the first argument.";
    return 1;
  }

  using sudoku::operator>>;
  using sudoku::operator<<;

  sudoku::Table t = sudoku::read_board(argv[1]);
  std::cout << "Start:" << std::endl;
  std::cout << t;

  auto t_end = sudoku::algorithm2(t);
  std::cout << "End - algorithm2:" << std::endl;
  if(t_end) std::cout << *t_end;
  else {
      std::cout << "Failed." << std::endl;
      return 1;
  }

  return 0;
}
