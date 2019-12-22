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

TEST(Intersection, origin)
{
    aoc::Segment const vert{aoc::Point{0, 10}, aoc::Point{0, -10}};
    aoc::Segment const hor{aoc::Point{10, 0}, aoc::Point{-10, 0}};

    auto const intersection = aoc::intersection_point(vert, hor);
    ASSERT_TRUE(intersection);
    aoc::Point const origin{0, 0};
    ASSERT_EQ(*intersection, origin);
}

TEST(Intersection, multi_origin)
{
    aoc::Segment const vert{aoc::Point{0, 10}, aoc::Point{0, -10}};
    std::vector<aoc::Segment> const hors{
        aoc::Segment{aoc::Point{-10, 0}, aoc::Point{10, 0}}};

    std::vector<aoc::Point> points;
    aoc::check_intersections(vert, hors, points);
    ASSERT_EQ(1, points.size());
    aoc::Point const origin{0, 0};
    ASSERT_EQ(origin, points.front());
    ASSERT_EQ(0, aoc::distance(origin, points.front()));
}

TEST(Intersection, multiple)
{
    aoc::Segment const vert{aoc::Point{0, 10}, aoc::Point{0, -10}};
    std::vector<aoc::Segment> const hors{
        aoc::Segment{aoc::Point{-10, 9}, aoc::Point{10, 9}},
        aoc::Segment{aoc::Point{-10, 8}, aoc::Point{10, 8}}};

    std::vector<aoc::Point> points;
    aoc::check_intersections(vert, hors, points);
    ASSERT_EQ(2, points.size());
    // aoc::Point const origin{0, 8};
    // ASSERT_EQ(origin, closest->first);
    // ASSERT_EQ(8, closest->second);
}

TEST(Intersection, none)
{
    aoc::Segment const vert{aoc::Point{0, 10}, aoc::Point{0, -10}};
    std::vector<aoc::Segment> const hors{
        aoc::Segment{aoc::Point{-10, 20}, aoc::Point{10, 20}}};

    std::vector<aoc::Point> points;
    aoc::check_intersections(vert, hors, points);
    ASSERT_TRUE(points.empty());
}
