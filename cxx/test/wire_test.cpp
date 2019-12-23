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

namespace
{
    template <std::size_t FIRST_OFFSETS_COUNT, std::size_t SECOND_OFFSETS_COUNT>
    void full_example_helper(
        std::array<std::pair<int, int>, FIRST_OFFSETS_COUNT> const &
            first_offsets,
        std::array<std::pair<int, int>, SECOND_OFFSETS_COUNT> const &
            second_offsets,
        std::size_t expected_cost)
    {
        auto const first_wire = make_ordered_wire(first_offsets);
        auto const second_wire = make_ordered_wire(second_offsets);

        std::vector<aoc::Point> intersection_points;
        auto iterate_verticals = [&intersection_points](auto const & a,
                                                        auto const & b) {
            std::for_each(std::begin(a.vertical), std::end(a.vertical),
                          [&intersection_points, &b](auto const & segment) {
                              aoc::check_intersections(segment, b.horizontal,
                                                       intersection_points);
                          });
        };

        iterate_verticals(first_wire, second_wire);
        iterate_verticals(second_wire, first_wire);

        std::sort(std::begin(intersection_points),
                  std::end(intersection_points));
        auto const first_step_costs =
            aoc::calculate_step_cost(intersection_points, first_wire);
        auto const second_step_costs =
            aoc::calculate_step_cost(intersection_points, second_wire);

        auto minimum_cost =
            aoc::minimum_total_step_cost(first_step_costs, second_step_costs);

        ASSERT_EQ(expected_cost, minimum_cost);
    }
} // namespace

TEST(StepCount, full_example1)
{
    static std::array<std::pair<int, int>, 4> const first_offsets = {
        std::make_pair(8, 0),  // R8
        std::make_pair(0, 5),  // U5
        std::make_pair(-5, 0), // L5
        std::make_pair(0, -3)  // D3
    };
    static std::array<std::pair<int, int>, 4> const second_offsets = {
        std::make_pair(0, 7),  // U7
        std::make_pair(6, 0),  // R6
        std::make_pair(0, -4), // D4
        std::make_pair(-4, 0)  // L4
    };

    full_example_helper(first_offsets, second_offsets, 30);
}

TEST(StepCount, full_example2)
{
    static std::array<std::pair<int, int>, 9> const first_offsets = {
        std::make_pair(75, 0),  // R75
        std::make_pair(0, -30), // D30
        std::make_pair(83, 0),  // R83
        std::make_pair(0, 83),  // U83
        std::make_pair(-12, 0), // L12
        std::make_pair(0, -49), // D49
        std::make_pair(71, 0),  // R71
        std::make_pair(0, 7),   // U7
        std::make_pair(-72, 0)  // L72
    };
    static std::array<std::pair<int, int>, 8> const second_offsets = {
        std::make_pair(0, 62),  // U62
        std::make_pair(66, 0),  // R66
        std::make_pair(0, 55),  // U55
        std::make_pair(34, 0),  // R34
        std::make_pair(0, -71), // D71
        std::make_pair(55, 0),  // R55
        std::make_pair(0, -58), // D58
        std::make_pair(83, 0),  // R83
    };

    full_example_helper(first_offsets, second_offsets, 610);
}

TEST(StepCount, full_example3)
{
    static std::array<std::pair<int, int>, 11> const first_offsets = {
        std::make_pair(98, 0),  // R98
        std::make_pair(0, 47),  // U47
        std::make_pair(26, 0),  // R26
        std::make_pair(0, -63), // D63
        std::make_pair(33, 0),  // R33
        std::make_pair(0, 87),  // U87
        std::make_pair(62, 0),  // L62
        std::make_pair(0, -20), // D20
        std::make_pair(33, 0),  // R33
        std::make_pair(0, 53),  // U53
        std::make_pair(51, 0),  // R51
    };
    static std::array<std::pair<int, int>, 10> const second_offsets = {
        std::make_pair(0, 98),  // U98
        std::make_pair(91, 0),  // R91
        std::make_pair(0, -20), // D20
        std::make_pair(16, 0),  // R16
        std::make_pair(0, -67), // D67
        std::make_pair(40, 0),  // R40
        std::make_pair(0, 7),   // U7
        std::make_pair(15, 0),  // R15
        std::make_pair(0, 6),   // U6
        std::make_pair(7, 0),   // R7
    };

    full_example_helper(first_offsets, second_offsets, 410);
}
