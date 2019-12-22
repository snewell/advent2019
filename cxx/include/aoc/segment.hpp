#ifndef AOC_SEGMENT_HPP
#define AOC_SEGMENT_HPP 1

#include <vector>

#include <aoc/point.hpp>

namespace aoc
{
    struct Segment
    {
        Segment(Point a, Point b);

        Point first;
        Point second;
    };

    bool operator==(Segment lhs, Segment rhs) noexcept;

    bool operator<(Segment lhs, Segment rhs) noexcept;

    std::optional<Point> intersection_point(Segment vert, Segment hor);

    std::optional<std::pair<Point, std::size_t>>
    closest_intersection(Segment vert,
                         std::vector<Segment> const & horizontals);
} // namespace aoc

#endif
