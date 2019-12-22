#include <algorithm>
#include <cassert>
#include <charconv>
#include <iostream>
#include <optional>
#include <vector>

#include <aoc/segment.hpp>

namespace
{
    struct Wire
    {
        std::vector<aoc::Segment> horizontal;
        std::vector<aoc::Segment> vertical;
    };

    Wire read_wire()
    {
        Wire ret;
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
            if(first_point.x == next_point.x)
            {
                // horizontal line
                ret.horizontal.push_back(aoc::Segment{first_point, next_point});
            }
            else
            {
                assert(first_point.y == next_point.y);
                ret.vertical.push_back(aoc::Segment{first_point, next_point});
            }
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

    return 0;
}
