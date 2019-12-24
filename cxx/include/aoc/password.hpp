#ifndef AOC_PASSWORD_H
#define AOC_PASSWORD_H 1

#include <string>

namespace aoc
{
    std::string raise_floor(std::string const & min);

    std::string lower_ceiling(std::string const & max);

    std::size_t count_possible_endings(std::string base,
                                       std::size_t prefix_length);
} // namespace aoc

#endif
