#include <aoc/orbit.hpp>

#include <gtest/gtest.h>

TEST(Orbit, trivial)
{
    aoc::SolarSystem solar_system;
    solar_system.emplace("COM", "A");
    solar_system.emplace("COM", "B");
    solar_system.emplace("COM", "C");

    auto const orbits = aoc::count_orbits(solar_system, "COM");
    ASSERT_EQ(3, orbits);
}

TEST(Orbit, recursive)
{
    aoc::SolarSystem solar_system;
    solar_system.emplace("COM", "A");
    solar_system.emplace("A", "B");
    solar_system.emplace("B", "C");

    auto const orbits = aoc::count_orbits(solar_system, "COM");
    // COM <- A
    // COM <- A <- B
    // COM <------ B
    // COM <- A <- B <- C
    // COM <------ B <- C
    // COM <----------- C
    ASSERT_EQ(6, orbits);
}

TEST(Orbit, complex_example)
{
    /*
     *         G - H       J - K - L
     *        /           /
     * COM - B - C - D - E - F
     *                \
     *                 I
     */
    aoc::SolarSystem solar_system;
    solar_system.emplace("B", "G");
    solar_system.emplace("G", "H");
    solar_system.emplace("E", "J");
    solar_system.emplace("J", "K");
    solar_system.emplace("K", "L");
    solar_system.emplace("COM", "B");
    solar_system.emplace("B", "C");
    solar_system.emplace("C", "D");
    solar_system.emplace("D", "E");
    solar_system.emplace("E", "F");
    solar_system.emplace("D", "I");

    auto const orbits = aoc::count_orbits(solar_system, "COM");
    ASSERT_EQ(42, orbits);
}

TEST(Orbit, parse_complex)
{
    std::istringstream input{"COM)B\n"
                             "B)C\n"
                             "C)D\n"
                             "D)E\n"
                             "E)F\n"
                             "B)G\n"
                             "G)H\n"
                             "D)I\n"
                             "E)J\n"
                             "J)K\n"
                             "K)L"};
    auto solar_system = aoc::parse_orbits(input);
    auto const orbits = aoc::count_orbits(solar_system, "COM");
    ASSERT_EQ(42, orbits);
}
