#include <aoc/wire.hpp>

#include <algorithm>
#include <cassert>

namespace
{
    void add_segment_helper(std::vector<aoc::Segment> & segments,
                            aoc::Segment segment)
    {
        auto it =
            std::upper_bound(std::begin(segments), std::end(segments), segment);
        segments.insert(it, segment);
    }
} // namespace

namespace aoc
{
    void Wire::add_segment(aoc::Point first, aoc::Point second)
    {
        Segment segment{first, second};
        if(segment.first.y == segment.second.y)
        {
            // horizontal
            add_segment_helper(horizontal, segment);
        }
        else
        {
            // vertical
            assert(segment.first.x == segment.second.x);
            add_segment_helper(vertical, segment);
        }
    }

    OrderedWire::OrderedWire()
    {
        point_sequence.push_back(aoc::Point{0, 0});
    }

    void OrderedWire::add_segment(aoc::Point first, aoc::Point second)
    {
        Wire::add_segment(first, second);
        assert(!(point_sequence.empty()));
        assert((point_sequence.back().x == second.x) ||
               (point_sequence.back().y == second.y));
        point_sequence.push_back(second);
    }

    std::unordered_map<aoc::Point, std::size_t>
    calculate_step_cost(std::vector<aoc::Point> const & points,
                        aoc::OrderedWire const & wire)
    {
        assert(std::is_sorted(std::begin(points), std::end(points)));
        std::unordered_map<aoc::Point, std::size_t> ret;
        auto local_cost = 0;
        auto const point_b = std::begin(points);
        auto const point_e = std::end(points);
        std::adjacent_find(
            std::begin(wire.point_sequence), std::end(wire.point_sequence),
            [&ret, point_b, point_e, &local_cost](auto first_point,
                                                  auto second_point) {
                auto check_points = [&ret, local_cost, first_point](
                                        auto first, auto second, auto pred) {
                    std::for_each(
                        first, second,
                        [&ret, &local_cost, first_point, pred](auto point) {
                            if(pred(first_point, point))
                            {
                                auto existing_cost = ret.find(point);
                                if(existing_cost == std::end(ret))
                                {
                                    auto const total_cost =
                                        local_cost +
                                        aoc::distance(first_point, point);
                                    ret.emplace(point, total_cost);
                                }
                            }
                        });
                };

                if(first_point.x == second_point.x)
                {
                    // vertical
                    auto first = std::lower_bound(
                        point_b, point_e,
                        aoc::Point{first_point.x,
                                   std::numeric_limits<int>::max()});
                    auto second = std::lower_bound(
                        first, point_e,
                        aoc::Point{first_point.x,
                                   std::numeric_limits<int>::min()});
                    check_points(first, second,
                                 [](auto p1, auto p2) { return p1.x == p2.x; });
                }
                else
                {
                    // horizontal
                    assert(first_point.y == second_point.y);
                    auto first = std::lower_bound(
                        point_b, point_e,
                        aoc::Point{std::numeric_limits<int>::min(),
                                   first_point.y});
                    auto second = std::lower_bound(
                        first, point_e,
                        aoc::Point{std::numeric_limits<int>::max(),
                                   first_point.y});
                    check_points(first, second,
                                 [](auto p1, auto p2) { return p1.y == p2.y; }

                    );
                }
                auto const new_distance =
                    aoc::distance(first_point, second_point);
                local_cost += new_distance;
                return false;
            });
        assert(points.size() == ret.size());
        return ret;
    }

    using StepCosts = std::unordered_map<aoc::Point, std::size_t>;

    std::size_t minimum_total_step_cost(StepCosts first_costs,
                                        StepCosts second_costs)
    {
        auto b = std::begin(first_costs);
        auto const e = std::end(first_costs);

        auto second_it = second_costs.find(b->first);
        assert(second_it != std::end(second_costs));
        auto min = b->second + second_it->second;
        std::for_each(std::next(b, 1), e,
                      [&min, &second_costs](auto const & p) {
                          auto const second_it = second_costs.find(p.first);
                          assert(second_it != std::end(second_costs));
                          auto cost = p.second + second_it->second;
                          min = std::min(min, cost);
                      });

        return min;
    }
} // namespace aoc
