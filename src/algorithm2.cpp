#include "algorithm2.hpp"
#include "common.hpp"
#include <algorithm>
#include <iostream>
#include <optional>

namespace sudoku {

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

std::optional<Admitted> algorithm2_rec(Admitted admitted_table, int &iterations,
                                       int max_iterations,
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
                       return algorithm2_rec(admitted_table_rec, iterations,
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

std::optional<Table> algorithm2(Table t, int max_iterations) {

  Admitted admitted_table = table_to_admitted(t);
  int iterations = 0;
  std::vector<int> cs{1};

  if (auto res = algorithm2_rec(admitted_table, iterations, max_iterations, cs);
      res)
    return admitted_to_table(*res);
  else
    return t;
}

} // namespace sudoku
