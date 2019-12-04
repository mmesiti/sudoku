#include "common.hpp"

namespace sudoku {
std::optional<Table> algorithm1(Table t, int max_iterations = 10000);

std::set<std::vector<Assumption>>
get_simple_assumption_list(const Admitted &admitted_table,
                           int max_parallel = 1);

} // namespace sudoku
