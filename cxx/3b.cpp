#include <algorithm>
#include <cassert>
#include <charconv>
#include <fstream>
#include <iostream>
#include <limits>

#include <aoc/segment.hpp>
#include <aoc/wire.hpp>

namespace
{
    aoc::OrderedWire read_wire(std::istream & input)
    {
        aoc::OrderedWire ret;
        std::string line;
        std::getline(input, line);

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
            ret.add_segment(first_point, next_point);
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

    auto read_wires(std::istream & input)
    {
        auto first_wire = read_wire(input);
        auto second_wire = read_wire(input);
        return std::make_pair(first_wire, second_wire);
    }
} // namespace

int main(int argc, char ** argv)
{
    auto [first_wire, second_wire] = [argc, argv]() {
        if(argc == 1)
        {
            return read_wires(std::cin);
        }
        else
        {
            std::ifstream input{argv[1]};
            return read_wires(input);
        }
    }();
    /*
    read_wire();
    auto second_wire = read_wire();
    */

    std::vector<aoc::Point> points;
    auto iterate_verticals = [&points](auto const & a, auto const & b) {
        std::for_each(std::begin(a.vertical), std::end(a.vertical),
                      [&points, &b](auto const & segment) {
                          aoc::check_intersections(segment, b.horizontal,
                                                   points);
                      });
    };

    iterate_verticals(first_wire, second_wire);
    iterate_verticals(second_wire, first_wire);

    std::sort(std::begin(points), std::end(points));
    auto first_costs = calculate_step_cost(points, first_wire);
    auto second_costs = calculate_step_cost(points, second_wire);

    auto b = std::begin(first_costs);
    auto const e = std::end(first_costs);

    auto second_it = second_costs.find(b->first);
    assert(second_it != std::end(second_costs));
    auto min = b->second + second_it->second;
    std::for_each(std::next(b, 1), e, [&min, &second_costs](auto const & p) {
        auto const second_it = second_costs.find(p.first);
        assert(second_it != std::end(second_costs));
        auto cost = p.second + second_it->second;
        min = std::min(min, cost);
    });
    std::cout << min << '\n';
    return 0;
}