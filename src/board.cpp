#include "../include/board.hpp"
#include <algorithm>
#include <fstream>
#include <iostream> // DEBUG
#include <map>
#include <optional>
#include <set>
#include <sstream>
#include <string>

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
  ;
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

std::set<std::vector<Assumption>>
get_simple_assumption_list(const Admitted &admitted_table, int max_parallel) {
  std::set<std::vector<Assumption>> assumptions;
  for (int i = 0; i < 9; ++i)
    for (int j = 0; j < 9; ++j) {

      auto f = [&](auto imap, auto jmap, auto kmap) {
        // i,j,k
        int count = 0;
        for (int k = 0; k < 9; ++k)
          count +=
              (admitted_table[imap(i, j, k)][jmap(i, j, k)][kmap(i, j, k)] ? 1
                                                                           : 0);
        if (count == max_parallel) {
          std::vector<Assumption> exclusive_assumptions;
          for (int k = 0; k < 9; ++k)
            if (admitted_table[imap(i, j, k)][jmap(i, j, k)][kmap(i, j, k)])
              exclusive_assumptions.push_back(
                  std::make_tuple(imap(i, j, k), jmap(i, j, k), kmap(i, j, k)));
          assumptions.insert(exclusive_assumptions);
        }
      };

      // from "top"
      f([](int i, int j, int k) { return i; },
        [](int i, int j, int k) { return j; },
        [](int i, int j, int k) { return k; });
      // from "side"
      f([](int i, int j, int k) { return j; },
        [](int i, int j, int k) { return k; },
        [](int i, int j, int k) { return i; });
      // from "front"
      f([](int i, int j, int k) { return k; },
        [](int i, int j, int k) { return i; },
        [](int i, int j, int k) { return j; });
    }
  return assumptions;
}

std::vector<Assumption>
get_single_exclusive_assumption(const Admitted &admitted_table) {
  std::vector<Assumption> exclusive_assumptions;
  for (int max_parallel = 0; max_parallel < 9; ++max_parallel)
    for (int i = 0; i < 9; ++i)
      for (int j = 0; j < 9; ++j) {

        auto f = [&](auto imap, auto jmap, auto kmap) {
          // i,j,k
          int count = 0;
          for (int k = 0; k < 9; ++k)
            count +=
                (admitted_table[imap(i, j, k)][jmap(i, j, k)][kmap(i, j, k)]
                     ? 1
                     : 0);
          if (count == max_parallel) {
            for (int k = 0; k < 9; ++k)
              if (admitted_table[imap(i, j, k)][jmap(i, j, k)][kmap(i, j, k)]) {
                auto assumption = std::make_tuple(imap(i, j, k), jmap(i, j, k),
                                                  kmap(i, j, k));

                if (not verify_assumption(assumption, admitted_table)) {
                  exclusive_assumptions.push_back(assumption);
                }
              }
          }
          return exclusive_assumptions.size() != 0;
        };

        // from "top"
        if (f([](int i, int j, int k) { return i; },
              [](int i, int j, int k) { return j; },
              [](int i, int j, int k) { return k; }) ||
            // from "side"
            f([](int i, int j, int k) { return j; },
              [](int i, int j, int k) { return k; },
              [](int i, int j, int k) { return i; }) ||
            // from "front"
            f([](int i, int j, int k) { return k; },
              [](int i, int j, int k) { return i; },
              [](int i, int j, int k) { return j; }))
          return exclusive_assumptions;
      }

  return exclusive_assumptions;
}

bool is_complete(const Admitted &admitted) {
  return std::all_of(admitted.begin(), admitted.end(), [](auto &row) {
    return all_of(row.begin(), row.end(), [](auto &row_el) {
      return std::count(row_el.begin(), row_el.end(), true) == 1;
    });
  });
}

std::optional<Table> heuristics1(Table t, int max_iterations) {
  int iteration_count = 0;

  std::optional<Table> res;

  Admitted admitted_table = table_to_admitted(t);
  while (not res and iteration_count < max_iterations) {
    auto assumptions = sudoku::get_simple_assumption_list(admitted_table);

    for (auto &exclusive_assumptions : assumptions) {
      auto admitted_tables = sudoku::apply_parallel_assumptions(
          exclusive_assumptions, admitted_table);
      admitted_table = admitted_tables[0];
      auto it = std::find_if(admitted_tables.begin(), admitted_tables.end(),
                             is_complete);

      if (it != admitted_tables.end()) {
        res = admitted_to_table(*it);
        break;
      }
    }
    ++iteration_count;
  }
  std::cout << "Iteration count: " << iteration_count << std::endl;
  return res;
}

std::optional<Admitted> heuristics2_rec(Admitted admitted_table,
                                        int &iterations, int max_iterations,
                                        std::vector<int> &cs) {
  std::optional<Admitted> res;
  if (iterations > max_iterations)
    return res;
  iterations++;

  auto exclusive_assumptions = get_single_exclusive_assumption(admitted_table);
  for (auto i = cs.begin(); i != cs.end(); ++i) {
    if (*i == 0)
      std::cout << " ";
    if (*i == 1 and i == (--cs.end()))
      std::cout << "\u255A";
    if (*i > 0 and i != (--cs.end()))
      std::cout << "\u2551";
    if (*i > 1 and i == (--cs.end()))
      std::cout << "\u2560";
  }

  std::cout << "n exclusive_assumptions: " << exclusive_assumptions.size();
  for (Assumption a : exclusive_assumptions) {
    std::cout << " (" << std::get<0>(a) + 1 << ",";
    std::cout << std::get<1>(a) + 1 << ",";
    std::cout << std::get<2>(a) + 1 << ") ";
  }
  std::cout << ",";

  auto admitted_tables =
      sudoku::apply_parallel_assumptions(exclusive_assumptions, admitted_table);
  std::cout << "n admitted_tables: " << admitted_tables.size() << std::endl;

  (*cs.rbegin())--;
  cs.push_back(admitted_tables.size());

  if (admitted_tables.size() != 0) {

    auto it = std::find_if(admitted_tables.begin(), admitted_tables.end(),
                           is_complete);

    if (it != admitted_tables.end()) {
      res = *it;
    } else { // recursion
      std::vector<std::optional<Admitted>> solutions;
      solutions.resize(admitted_tables.size());
      std::transform(admitted_tables.begin(), admitted_tables.end(),
                     solutions.begin(), [&](Admitted admitted_table_rec) {
                       return heuristics2_rec(admitted_table_rec, iterations,
                                              max_iterations, cs);
                     });

      auto result = std::find_if(solutions.begin(), solutions.end(),
                                 [](auto x) { return bool(x); });

      if (result != solutions.end())
        res = *result;
    }
  }
  cs.pop_back();
  return res;
}

std::optional<Table> heuristics2(Table t, int max_iterations) {

  Admitted admitted_table = table_to_admitted(t);
  int iterations = 0;
  std::vector<int> cs{1};

  if (auto res =
          heuristics2_rec(admitted_table, iterations, max_iterations, cs);
      res)
    return admitted_to_table(*res);
  else
    return t;
}

} // namespace sudoku
