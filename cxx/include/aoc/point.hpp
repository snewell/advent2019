#ifndef AOC_POINT_HPP
#define AOC_POINT_HPP 1

#include <optional>
#include <unordered_map>

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

namespace std
{
    template <>
    struct hash<aoc::Point>
    {
        std::size_t operator()(aoc::Point const & p) const noexcept
        {
            return (static_cast<std::size_t>(p.x) << 32) | p.y;
        }
    };
} // namespace std

#endif
