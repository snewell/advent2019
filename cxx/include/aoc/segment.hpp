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

    void check_intersections(Segment vert,
                             std::vector<Segment> const & horizontals,
                             std::vector<Point> & points);
} // namespace aoc

#endif
