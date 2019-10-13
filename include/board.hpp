#include <array>
#include <ostream>
#include <istream>

namespace sudoku {
using table = std::array<std::array<char, 9>, 9>;
using admitted = std::array<std::array<std::array<bool, 9>, 9>, 9>;

std::istream& operator<<(std::istream&, const table&);
std::ostream& operator>>(std::ostream&, table&);

std::istream& operator<<(std::istream&, const admitted&);


} // namespace sudoku
