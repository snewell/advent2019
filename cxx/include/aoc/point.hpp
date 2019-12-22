#ifndef AOC_POINT_HPP
#define AOC_POINT_HPP 1

#include <optional>

#include <aoc/point.hpp>

namespace aoc
{
    struct Point
    {
        int x;
        int y;
    };

    std::size_t distance(Point first, Point second) noexcept;

    bool operator==(Point lhs, Point rhs) noexcept;

    bool operator!=(Point lhs, Point rhs) noexcept;

    bool operator<(Point lhs, Point rhs) noexcept;
} // namespace aoc

#endif
