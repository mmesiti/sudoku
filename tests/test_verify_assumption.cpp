#include "common.hpp"
#include "algorithm1.hpp"
#include <iostream>

int main(int argc, char **argv) {

  if (argc < 2) {
    std::cout << "Pass the file name as the first argument.";
    return 1;
  }

  using sudoku::operator<<;
  using sudoku::operator>>;

  sudoku::Table t = sudoku::read_board(argv[1]);

  auto admitted_table = sudoku::table_to_admitted(t);

  auto all_assumptions = sudoku::get_simple_assumption_list(admitted_table, 9);

  for (auto &assumption_group : all_assumptions)
    for (auto &assumption : assumption_group) {
      auto adm = sudoku::apply_single_assumption(assumption, admitted_table);
      if (adm) {
        if (not sudoku::verify_assumption(assumption, *adm)) {
          std::cout << "Assumption " << std::get<0>(assumption) + 1 << ","
                    << std::get<1>(assumption) + 1 << ","
                    << std::get<2>(assumption) + 1
                    << " is not compatible with table " << std::endl
                    << t;

          return 1;
        }
      } 
    }

  return 0;
}
