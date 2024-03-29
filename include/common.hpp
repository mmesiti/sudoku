#ifndef COMMON_H
#define COMMON_H
#include <array>
#include <istream>
#include <optional>
#include <ostream>
#include <set>
#include <tuple>
#include <vector>

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

std::optional<Admitted> apply_single_assumption(Assumption assumption,
                                                const Admitted &admitted_table);

std::vector<Admitted>
apply_parallel_assumptions(const std::vector<Assumption> &parallel_assumptions,
                           const Admitted &);
bool verify_assumption(Assumption assumption, const Admitted &admitted_table);

bool is_complete(const Admitted &admitted);

} // namespace sudoku
#endif
