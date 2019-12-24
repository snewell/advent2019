#ifndef AOC_ORBIT_HPP
#define AOC_ORBIT_HPP 1

#include <unordered_map>

namespace aoc
{
    using SolarSystem = std::unordered_multimap<std::string, std::string>;

    std::size_t count_orbits(SolarSystem const & solar_system,
                             std::string const & center, std::size_t depth = 0);
} // namespace aoc

#endif
