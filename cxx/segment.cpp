#include <aoc/segment.hpp>

#include <algorithm>
#include <cassert>

namespace aoc
{
    std::optional<Point> intersection_point(Segment vert, Segment hor)
    {
        assert(vert.first.x == vert.second.x);
        assert(hor.first.y == hor.second.y);
        if((vert.first.y >= hor.first.y) && (vert.second.y <= hor.second.y))
        {
            if((hor.first.x >= vert.first.x) && (hor.second.x <= vert.second.x))
            {
                return Point{vert.first.x, hor.first.y};
            }
        }
        return std::nullopt;
    }

    std::optional<Point>
    closest_intersection(Segment vert, std::vector<Segment> const & horizontals)
    {
        std::optional<Point> ret = std::nullopt;
        auto minimum_distance = std::numeric_limits<std::size_t>::max();
        std::for_each(std::begin(horizontals), std::end(horizontals),
                      [vert, &ret, &minimum_distance](auto const & segment) {
                          auto intersection = intersection_point(vert, segment);
                          if(intersection)
                          {
                              auto distance = static_cast<std::size_t>(
                                  std::abs(intersection->x) +
                                  std::abs(intersection->y));
                              if(distance < minimum_distance)
                              {
                                  minimum_distance = distance;
                                  ret = intersection;
                              }
                          }
                      });
        return ret;
    }
} // namespace aoc
