#include <aoc/orbit.hpp>

#include <gtest/gtest.h>

TEST(Orbit, trivial)
{
    aoc::Satelites satelites;
    satelites.emplace("COM", "A");
    satelites.emplace("COM", "B");
    satelites.emplace("COM", "C");

    auto const orbits = aoc::count_orbits(satelites, "COM");
    ASSERT_EQ(3, orbits);
}

TEST(Orbit, recursive)
{
    aoc::Satelites satelites;
    satelites.emplace("COM", "A");
    satelites.emplace("A", "B");
    satelites.emplace("B", "C");

    auto const orbits = aoc::count_orbits(satelites, "COM");
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
    aoc::Satelites satelites;
    satelites.emplace("B", "G");
    satelites.emplace("G", "H");
    satelites.emplace("E", "J");
    satelites.emplace("J", "K");
    satelites.emplace("K", "L");
    satelites.emplace("COM", "B");
    satelites.emplace("B", "C");
    satelites.emplace("C", "D");
    satelites.emplace("D", "E");
    satelites.emplace("E", "F");
    satelites.emplace("D", "I");

    auto const orbits = aoc::count_orbits(satelites, "COM");
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
    auto satelites = aoc::parse_satelites(input);
    auto const orbits = aoc::count_orbits(satelites, "COM");
    ASSERT_EQ(42, orbits);
}

TEST(Orbit, DISABLED_complex_hops)
{
    /*                          YOU
     *                          /
     *         G - H       J - K - L
     *        /           /
     * COM - B - C - D - E - F
     *                \
     *                 I - SAN
     */
    aoc::SolarSystem solar_system;
    solar_system.emplace("YOU", "K");
    solar_system.emplace("G", "B");
    solar_system.emplace("H", "G");
    solar_system.emplace("J", "E");
    solar_system.emplace("K", "J");
    solar_system.emplace("L", "K");
    solar_system.emplace("B", "COM");
    solar_system.emplace("C", "B");
    solar_system.emplace("D", "C");
    solar_system.emplace("E", "D");
    solar_system.emplace("F", "E");
    solar_system.emplace("I", "D");
    solar_system.emplace("SAN", "I");

    auto const hops = aoc::count_hops(solar_system, "YOU", "SAN");
    ASSERT_EQ(4, hops);
}
