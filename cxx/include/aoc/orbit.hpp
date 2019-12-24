#ifndef AOC_ORBIT_HPP
#define AOC_ORBIT_HPP 1

#include <istream>
#include <unordered_map>

namespace aoc
{
    using Satelites = std::unordered_multimap<std::string, std::string>;

    using SolarSystem = std::unordered_map<std::string, std::string>;

    Satelites parse_satelites(std::istream & input);

    std::size_t count_orbits(Satelites const & satelites,
                             std::string const & center, std::size_t depth = 0);

    std::size_t count_hops(SolarSystem const & solar_system,
                           std::string const & first,
                           std::string const & second);
} // namespace aoc

#endif
