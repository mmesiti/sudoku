#include "common.hpp"
#include "algorithm2.hpp"
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

  auto t_end = sudoku::algorithm2(t);
  std::cout << "End - algorithm2:" << std::endl;
  if(t_end) std::cout << *t_end;
  else { 
      std::cout << "Failed" << std::endl;
      return 1;
  }
 

  if (t_end != t_end_read)
    return 1;
  else
    return 0;
}
