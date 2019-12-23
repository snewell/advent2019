#include <aoc/wire.hpp>

#include <gtest/gtest.h>

namespace
{
    template <std::size_t STEP_COUNT>
    aoc::OrderedWire
    make_ordered_wire(std::array<std::pair<int, int>, STEP_COUNT> const & steps)
    {
        aoc::OrderedWire wire;

        aoc::Point current{0, 0};
        std::for_each(
            std::begin(steps), std::end(steps),
            [&current, &wire](auto const & p) {
                aoc::Point next{current.x + p.first, current.y + p.second};
                wire.add_segment(current, next);
                current = next;
            });
        return wire;
    }
} // namespace

TEST(StepCount, example1)
{
    static std::array<std::pair<int, int>, 4> const offsets = {
        std::make_pair(8, 0),  // R8
        std::make_pair(0, 5),  // U5
        std::make_pair(-5, 0), // L5
        std::make_pair(0, -3)  // D3
    };

    auto const wire = make_ordered_wire(offsets);

    std::vector<aoc::Point> const intersection_points = {aoc::Point{3, 3},
                                                         aoc::Point{6, 5}};

    auto const step_counts =
        aoc::calculate_step_cost(intersection_points, wire);
    auto const count0 = step_counts.find(intersection_points[0]);
    auto const count1 = step_counts.find(intersection_points[1]);

    ASSERT_NE(count0, std::end(step_counts));
    ASSERT_EQ(20, count0->second);
    ASSERT_NE(count1, std::end(step_counts));
    ASSERT_EQ(15, count1->second);
}

TEST(StepCount, example2)
{
    static std::array<std::pair<int, int>, 4> const offsets = {
        std::make_pair(0, 7),  // U7
        std::make_pair(6, 0),  // R6
        std::make_pair(0, -4), // D4
        std::make_pair(-4, 0)  // L4
    };

    auto const wire = make_ordered_wire(offsets);

    std::vector<aoc::Point> const intersection_points = {aoc::Point{3, 3},
                                                         aoc::Point{6, 5}};

    auto const step_counts =
        aoc::calculate_step_cost(intersection_points, wire);
    auto const count0 = step_counts.find(intersection_points[0]);
    auto const count1 = step_counts.find(intersection_points[1]);

    ASSERT_NE(count0, std::end(step_counts));
    ASSERT_EQ(20, count0->second);
    ASSERT_NE(count1, std::end(step_counts));
    ASSERT_EQ(15, count1->second);
}
