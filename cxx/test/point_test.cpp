#include <aoc/point.hpp>

#include <gtest/gtest.h>

namespace
{
    aoc::Point const origin{0, 0};

    void distance_helper(aoc::Point a, aoc::Point b, std::size_t expected)
    {
        auto const first = aoc::distance(a, b);
        ASSERT_EQ(expected, first);
        auto const second = aoc::distance(b, a);
        ASSERT_EQ(expected, second);
    }
} // namespace

TEST(Point, distance_self)
{
    distance_helper(origin, origin, 0);
}

TEST(Point, distance_pos)
{
    distance_helper(origin, aoc::Point{10, 0}, 10);
}

TEST(Point, distance_neg)
{
    distance_helper(origin, aoc::Point{-10, 0}, 10);
}

TEST(Point, distance_cross)
{
    distance_helper(aoc::Point{10, 0}, aoc::Point{-10, 0}, 20);
}

TEST(Point, y_axis)
{
    aoc::Point const first{8, 0};
    aoc::Point const second{8, 5};
    distance_helper(first, second, 5);
}

TEST(Point, compare_self)
{
    ASSERT_EQ(origin, origin);
}

TEST(Point, compare_less_x)
{
    aoc::Point const a{-10, 0};
    aoc::Point const b{0, 100};
    ASSERT_LT(a, b);
}

TEST(Point, compare_equal_x_diff_y)
{
    aoc::Point const a{-10, 100};
    aoc::Point const b{-10, 10};
    ASSERT_LT(a, b);
}
