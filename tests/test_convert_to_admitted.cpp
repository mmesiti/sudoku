#include "common.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char **argv) {

  if (argc < 2) {
    std::cout << "Pass the file name as the first argument.";
    return 1;
  }

  using sudoku::operator<<;
  using sudoku::operator>>;

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

  auto admitted_table = sudoku::table_to_admitted(t);

  std::cout <<  admitted_table;

  std::cout << "Printing..." << std::endl;
  {
    std::stringstream ss_out;
    ss_out << sudoku::admitted_to_table(admitted_table);
    std::cout << ss_out.str();
    if(ss_in.str() != ss_out.str()) return 1;
  }
  std::cout << "Done." << std::endl;
  
  return 0;
}
