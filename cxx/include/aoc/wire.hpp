#ifndef AOC_WIRE_HPP
#define AOC_WIRE_HPP 1

#include <unordered_map>

#include <aoc/segment.hpp>

namespace aoc
{
    struct Wire
    {
        virtual void add_segment(aoc::Point first, aoc::Point second);

        std::vector<aoc::Segment> horizontal;
        std::vector<aoc::Segment> vertical;
    };

    struct OrderedWire : public Wire
    {
        OrderedWire();

        void add_segment(aoc::Point first, aoc::Point second) override;

        std::vector<aoc::Point> point_sequence;
    };

    std::unordered_map<aoc::Point, std::size_t>
    calculate_step_cost(std::vector<aoc::Point> const & points,
                        aoc::OrderedWire const & wire);

    using StepCosts = std::unordered_map<aoc::Point, std::size_t>;

    std::size_t minimum_total_step_cost(StepCosts first_costs,
                                        StepCosts second_costs);
} // namespace aoc

#endif
