#include <aoc/password.hpp>

#include <gtest/gtest.h>

TEST(Password, identity_floor)
{
    std::string const min{"111111"};
    auto const floor = aoc::raise_floor(min);
    ASSERT_EQ(min, floor);
}

TEST(Password, input_floor)
{
    std::string const min{"108457"};
    auto const floor = aoc::raise_floor(min);
    auto const expected_floor{"111111"};
    ASSERT_EQ(expected_floor, floor);
}

TEST(Password, identity_ceiling)
{
    std::string const max{"999999"};
    auto const ceiling = aoc::lower_ceiling(max);
    ASSERT_EQ(max, ceiling);
}

TEST(Password, input_ceiling)
{
    std::string const max{"562041"};
    auto const ceiling = aoc::lower_ceiling(max);
    auto const expected_ceiling{"559999"};
    ASSERT_EQ(expected_ceiling, ceiling);
}

TEST(Password, test_single)
{
    std::string const base{"123456"};
    auto count = aoc::count_possible_endings(base, 5);
    // count should be 5:
    //  123455
    //  123456
    //  123457
    //  123458
    //  123459
    ASSERT_EQ(5, count);
}

TEST(Password, test_multiple)
{
    std::string const base{"123888"};
    auto count = aoc::count_possible_endings(base, 4);
    // count should be 3:
    //  123888
    //  123889
    //  123899
    ASSERT_EQ(3, count);
}
