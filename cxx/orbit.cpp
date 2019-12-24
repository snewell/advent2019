#include <aoc/orbit.hpp>

#include <algorithm>

namespace aoc
{
    std::size_t count_orbits(SolarSystem const & solar_system,
                             std::string const & center, std::size_t depth)
    {
        auto const range = solar_system.equal_range(center);

        std::size_t ret = 0;
        std::for_each(range.first, range.second,
                      [depth, &solar_system, &ret](auto const & p) {
                          ret +=
                              count_orbits(solar_system, p.second, depth + 1);
                      });
        ret += depth;
        return ret;
    }
} // namespace aoc
