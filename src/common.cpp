#include "common.hpp"
#include <algorithm>
#include <fstream>
#include <iostream> // DEBUG
#include <map>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include "git_commit.h"

namespace sudoku {

const int missing = -1;

std::map<char, int> chartoint{{'1', 0}, {'2', 1},      {'3', 2}, {'4', 3},
                              {'5', 4}, {'6', 5},      {'7', 6}, {'8', 7},
                              {'9', 8}, {'*', missing}};

std::istream &operator>>(std::istream &input, Table &t) {

  for (auto &row : t) {
    for (int &el : row) {
      char e;
      input >> e;
      el = chartoint[e];
    }
  }
  return input;
}

std::ostream &operator<<(std::ostream &output, const Table &t) {

  for (auto &row : t) {
    for (auto &el : row)
      if (el == missing)
        output << '*';
      else
        output << el + 1;
    output << std::endl;
  }
  return output;
}

std::ostream &operator<<(std::ostream &output, const Admitted &t) {

  for (auto &row : t) {
    for (auto &row_el : row) {

      output << " (";
      for (int i = 0; i < 9; ++i) {
        if (row_el[i])
          output << i + 1;
      }
      output << ") ";
    }
    output << std::endl;
  }

  return output;
}

Table read_board(std::string filename) {

  Table t;
  std::fstream f(filename);
  f >> t;
  f.close();
  return t;
}

Admitted table_to_admitted(const Table &t) {
  Admitted admitted_cube;
  for (int i = 0; i < 9; ++i)
    for (int j = 0; j < 9; ++j) {
      if (t[i][j] == missing)
        for (auto &k : admitted_cube[i][j])
          k = true;
      else {
        for (auto &k : admitted_cube[i][j])
          k = false;
        admitted_cube[i][j][t[i][j]] = true;
      }
    }
  return admitted_cube;
}

Table admitted_to_table(const Admitted &admitted_table) {
  Table t;
  for (int i = 0; i < 9; ++i)
    for (int j = 0; j < 9; ++j) {
      if (std::count(admitted_table[i][j].begin(), admitted_table[i][j].end(),
                     true) > 1)
        t[i][j] = missing;
      else
        t[i][j] = std::find(admitted_table[i][j].begin(),
                            admitted_table[i][j].end(), true) -
                  admitted_table[i][j].begin();
    }
  return t;
}

std::optional<Admitted>
apply_single_assumption(Assumption assumption, const Admitted &admitted_table) {

  using std::get;
  std::optional<Admitted> res;
  int row = get<0>(assumption);
  int col = get<1>(assumption);
  int val = get<2>(assumption);
  Admitted new_admitted_table = admitted_table;
  // acting on the position
  std::fill(new_admitted_table[row][col].begin(),
            new_admitted_table[row][col].end(), false);
  // acting on the row
  for (int i = 0; i < 9; ++i)
    new_admitted_table[i][col][val] = false;
  // acting on the column
  for (int j = 0; j < 9; ++j)
    new_admitted_table[row][j][val] = false;

  // acting on the 3x3 cell
  for (int i = (row / 3) * 3; i < (row / 3 + 1) * 3; ++i)
    for (int j = (col / 3) * 3; j < (col / 3 + 1) * 3; ++j)
      new_admitted_table[i][j][val] = false;

  new_admitted_table[row][col][val] = true;
  // acting on the row
  if (not std::any_of(
          new_admitted_table.begin(), new_admitted_table.end(), [](auto &row) {
            return std::any_of(row.begin(), row.end(), [](auto &row_el) {
              return std::none_of(row_el.begin(), row_el.end(),
                                  [](bool el) { return el; });
            });
          })) {
    return res = new_admitted_table;
  }

  return res;
}

std::vector<Admitted>
apply_parallel_assumptions(const std::vector<Assumption> &parallel_assumptions,
                           const Admitted &admitted_table) {
  using std::get;
  std::vector<Admitted> solutions;
  for (auto &assumption : parallel_assumptions) {
    if (std::any_of(solutions.begin(), solutions.end(), [&](auto solution) {
          return verify_assumption(assumption, solution);
        }))
      continue;
    auto new_admitted_table =
        apply_single_assumption(assumption, admitted_table);
    if (new_admitted_table)
      solutions.push_back(*new_admitted_table);
  }

  return solutions;
}

bool verify_assumption(Assumption assumption, const Admitted &admitted_table) {

  using std::get;
  int row = get<0>(assumption);
  int col = get<1>(assumption);
  int val = get<2>(assumption);
  // acting on the row
  for (int i = 0; i < 9; ++i)
    if (i != row and admitted_table[i][col][val])
      return false;
  // acting on the column
  for (int j = 0; j < 9; ++j)
    if (j != col and admitted_table[row][j][val])
      return false;

  // acting on the 3x3 cell
  for (int i = (row / 3) * 3; i < (row / 3 + 1) * 3; ++i)
    for (int j = (col / 3) * 3; j < (col / 3 + 1) * 3; ++j)
      if ((i != row or j != col) and admitted_table[i][j][val])
        return false;

  return true;
}

bool is_complete(const Admitted &admitted) {
  return std::all_of(admitted.begin(), admitted.end(), [](auto &row) {
    return all_of(row.begin(), row.end(), [](auto &row_el) {
      return std::count(row_el.begin(), row_el.end(), true) == 1;
    });
  });
}


} // namespace sudoku
