#ifndef AOC_SEGMENT_HPP
#define AOC_SEGMENT_HPP 1

#include <vector>

#include <aoc/point.hpp>

namespace aoc
{
    struct Segment
    {
        Point first;
        Point second;
    };

    std::optional<Point> intersection_point(Segment vert, Segment hor);

    std::optional<Point>
    closest_intersection(Segment vert,
                         std::vector<Segment> const & horizontals);
} // namespace aoc

#endif
