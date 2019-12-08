#include "algorithm1.hpp"
#include "common.hpp"
#include <algorithm>
#include <iostream>
#include "git_commit.h"

namespace sudoku {

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

std::optional<Table> algorithm1(Table t, int max_iterations) {
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

} // namespace sudoku
