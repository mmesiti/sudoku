#include "algorithm1.hpp"
#include "algorithm2.hpp"
#include "common.hpp"
#include <iostream>
#include <map>
#include <cstdlib>
#include <functional>

int main(int argc, char **argv) {

  if (argc < 4) {
    std::cout << "Usage: " << argv[0] << "input expected_output [12]"
              << std::endl;
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

  int algchoice = std::atoi(argv[3]);
  std::map<int,std::function<decltype(sudoku::algorithm2)>> algorithms;
  algorithms[1] = sudoku::algorithm1;
  algorithms[2] = sudoku::algorithm2;

  auto t_end = algorithms[algchoice](t,10000);
  std::cout << "End - algorithm2:" << std::endl;
  if (t_end)
    std::cout << *t_end;
  else {
    std::cout << "Failed" << std::endl;
    return 1;
  }

  if (t_end != t_end_read)
    return 1;
  else
    return 0;
}
