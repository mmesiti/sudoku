#include <array>
#include <istream>
#include <ostream>
#include <tuple>
#include <vector>
#include <set>

namespace sudoku {
using Table = std::array<std::array<int, 9>, 9>;
using Admitted = std::array<std::array<std::array<bool, 9>, 9>, 9>;
using Assumption = std::tuple<int, int, int>;

std::istream &operator>>(std::istream &, Table &);
std::ostream &operator<<(std::ostream &, const Table &);

std::ostream &operator<<(std::ostream &, const Admitted &);

Table read_board(std::string);

Admitted table_to_admitted(const Table &t);
Table admitted_to_table(const Admitted &admitted_table);

std::vector<Admitted>
apply_parallel_assumptions(const std::vector<Assumption> &parallel_assumptions,
                           const Admitted &);

std::set<std::vector<Assumption>>
get_simple_assumption_list(const Admitted &admitted_table, int max_parallel = 1);

bool is_complete(const Admitted& admitted);

Table heuristics1(Table t, int max_iterations = 10000);
} // namespace sudoku
