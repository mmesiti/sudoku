#include "common.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>

int main(int argc, char **argv) {

  if (argc < 2) {
    std::cout << "Pass the file name as the first argument.";
    return 1;
  }

  using sudoku::operator>>;
  using sudoku::operator<<;

  sudoku::Table t;
  std::cout << "Reading... ";
  std::stringstream ss_in;
  {
    std::ifstream f(argv[1]);
    ss_in << f.rdbuf();
    std::cout << ss_in.str();
    f.close();
  }
  ss_in >> t;
  std::cout << "Done." << std::endl;

  std::cout << "Printing..." << std::endl;
  {
    std::stringstream ss_out;
    ss_out << t;
    std::cout << ss_out.str();
    if(ss_in.str() != ss_out.str()) return 1;
  }
  std::cout << "Done." << std::endl;

  return 0;
}
