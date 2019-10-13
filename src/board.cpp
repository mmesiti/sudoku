#include "../include/board.hpp"

namespace sudoku {

std::istream &operator>>(std::istream &input, table &t) {

  for (auto &row : t)
    for (auto &el : row)
      input >> el;

  return input;
}

std::ostream &operator<<(std::ostream &output, const table &t) {

  for (auto &row : t)
    for (auto &el : row)
      output << el;
  return output;
}

std::ostream &operator<<(std::ostream &output, const admitted &t) {

  for (auto &row : t)
    for (auto &row_el : row) {

      output << " (";
      for (auto &el : row_el)
        output << el
               << (el == *row_el.rbegin() ? std::string("") : std::string(","));
      output << ") ";
    }

  return output;
}

} // namespace sudoku
