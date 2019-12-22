#include <aoc/segment.hpp>

#include <gtest/gtest.h>

TEST(Intersection, intersect_origin)
{
    aoc::Segment const vert{aoc::Point{0, 10}, aoc::Point{0, -10}};
    aoc::Segment const hor{aoc::Point{10, 0}, aoc::Point{-10, 0}};

    auto const intersection = aoc::intersection_point(vert, hor);
    ASSERT_TRUE(intersection);
    aoc::Point const origin{0, 0};
    ASSERT_EQ(*intersection, origin);
}
