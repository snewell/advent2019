#include <aoc/segment.hpp>

#include <algorithm>
#include <cassert>

namespace aoc
{
    Segment::Segment(Point a, Point b)
      : first{a}
      , second{b}
    {
        assert(a != b);
        if(b < a)
        {
            std::swap(first, second);
        }
    }

    bool operator==(Segment lhs, Segment rhs) noexcept
    {
        return (lhs.first == rhs.first) && (lhs.second == rhs.second);
    }

    bool operator<(Segment lhs, Segment rhs) noexcept
    {
        if(lhs.first < rhs.first)
        {
            return true;
        }
        else if(lhs.first == rhs.first)
        {
            return lhs.second < rhs.second;
        }
        else
        {
            return false;
        }
    }

    std::optional<Point> intersection_point(Segment vert, Segment hor)
    {
        assert(vert.first.x == vert.second.x);
        assert(hor.first.y == hor.second.y);
        if((vert.first.y > hor.first.y) && (vert.second.y < hor.second.y))
        {
            if((hor.first.x < vert.first.x) && (hor.second.x > vert.second.x))
            {
                return Point{vert.first.x, hor.first.y};
            }
        }
        return std::nullopt;
    }

    void check_intersections(Segment vert,
                             std::vector<Segment> const & horizontals,
                             std::vector<Point> & points)
    {
        std::for_each(std::begin(horizontals), std::end(horizontals),
                      [vert, &points](auto const & segment) {
                          auto intersection = intersection_point(vert, segment);
                          if(intersection)
                          {
                              points.push_back(*intersection);
                          }
                      });
    }
} // namespace aoc
