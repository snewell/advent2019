#include <aoc/segment.hpp>

#include <gtest/gtest.h>

TEST(Segment, ctor_order)
{
    aoc::Point const a{10, 10};
    aoc::Point const b{-10, -10};

    aoc::Segment const first{a, b};
    aoc::Segment const second{b, a};
    ASSERT_EQ(first, second);
}

TEST(Intersection, intersect_origin)
{
    aoc::Segment const vert{aoc::Point{0, 10}, aoc::Point{0, -10}};
    aoc::Segment const hor{aoc::Point{10, 0}, aoc::Point{-10, 0}};

    auto const intersection = aoc::intersection_point(vert, hor);
    ASSERT_TRUE(intersection);
    aoc::Point const origin{0, 0};
    ASSERT_EQ(*intersection, origin);
}

TEST(Intersection, closest_origin)
{
    aoc::Segment const vert{aoc::Point{0, 10}, aoc::Point{0, -10}};
    std::vector<aoc::Segment> const hors{
        aoc::Segment{aoc::Point{-10, 0}, aoc::Point{10, 0}}};

    auto closest = aoc::closest_intersection(vert, hors);
    ASSERT_TRUE(closest);
    aoc::Point const origin{0, 0};
    ASSERT_EQ(origin, closest->first);
    ASSERT_EQ(0, closest->second);
}

TEST(Intersection, closest_iterative)
{
    aoc::Segment const vert{aoc::Point{0, 10}, aoc::Point{0, -10}};
    std::vector<aoc::Segment> const hors{
        aoc::Segment{aoc::Point{-10, 9}, aoc::Point{10, 9}},
        aoc::Segment{aoc::Point{-10, 8}, aoc::Point{10, 8}}};

    auto closest = aoc::closest_intersection(vert, hors);
    ASSERT_TRUE(closest);
    aoc::Point const origin{0, 8};
    ASSERT_EQ(origin, closest->first);
    ASSERT_EQ(8, closest->second);
}

TEST(Intersection, closest_none)
{
    aoc::Segment const vert{aoc::Point{0, 10}, aoc::Point{0, -10}};
    std::vector<aoc::Segment> const hors{
        aoc::Segment{aoc::Point{-10, 20}, aoc::Point{10, 20}}};

    auto closest = aoc::closest_intersection(vert, hors);
    ASSERT_FALSE(closest);
}
