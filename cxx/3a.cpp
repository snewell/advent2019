#include <algorithm>
#include <cassert>
#include <charconv>
#include <iostream>
#include <limits>

#include <aoc/segment.hpp>
#include <aoc/wire.hpp>

namespace
{
    aoc::Wire read_wire()
    {
        aoc::Wire ret;
        std::string line;
        std::getline(std::cin, line);

        aoc::Point first_point{0, 0};
        auto b = std::begin(line);
        auto const e = std::end(line);
        while(b != e)
        {
            auto it = std::find(b, e, ',');
            int distance;
            auto next_point = first_point;
            std::string_view const sv(
                line.data() + std::distance(std::begin(line), b) + 1,
                std::distance(b, it));
            std::from_chars(sv.data(), sv.data() + sv.size(), distance);
            switch(*b)
            {
            case 'R':
                next_point.x += distance;
                break;
            case 'L':
                next_point.x -= distance;
                break;

            case 'U':
                next_point.y += distance;
                break;
            case 'D':
                next_point.y -= distance;
                break;

            default:
                throw std::runtime_error{"Invalid input"};
                break;
            }
            ret.add_segment(aoc::Segment{first_point, next_point});
            first_point = next_point;
            if(*it != ',')
            {
                b = e;
            }
            else
            {
                b = std::next(it);
            }
        }
        return ret;
    }

} // namespace

int main()
{
    auto first_wire = read_wire();
    auto second_wire = read_wire();

    auto minimum_distance = std::numeric_limits<std::size_t>::max();
    auto iterate_verticals = [&minimum_distance](auto const & a,
                                                 auto const & b) {
        std::for_each(std::begin(a.vertical), std::end(a.vertical),
                      [&minimum_distance, &b](auto const & segment) {
                          auto segment_min =
                              aoc::closest_intersection(segment, b.horizontal);
                          if(segment_min)
                          {
                              minimum_distance = std::min(minimum_distance,
                                                          segment_min->second);
                          }
                      });
    };

    iterate_verticals(first_wire, second_wire);
    iterate_verticals(second_wire, first_wire);

    std::cout << minimum_distance << '\n';

    return 0;
}
