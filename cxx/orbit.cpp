#include <aoc/orbit.hpp>

#include <algorithm>

namespace aoc
{
    Satelites parse_satelites(std::istream & input)
    {
        Satelites ret;
        std::string orbit_data;
        while(input >> orbit_data)
        {
            auto const b = std::begin(orbit_data);
            auto const e = std::end(orbit_data);
            auto it = std::find(b, e, ')');
            ret.emplace(std::string{b, it}, std::string{std::next(it), e});
        }
        return ret;
    }

    SolarSystem parse_orbits(std::istream & input)
    {
        SolarSystem ret;
        std::string orbit_data;
        while(input >> orbit_data)
        {
            auto const b = std::begin(orbit_data);
            auto const e = std::end(orbit_data);
            auto it = std::find(b, e, ')');
            ret.emplace(std::string{std::next(it), e}, std::string{b, it});
        }
        return ret;
    }

    std::size_t count_orbits(Satelites const & satelites,
                             std::string const & center, std::size_t depth)
    {
        auto const range = satelites.equal_range(center);

        std::size_t ret = 0;
        std::for_each(range.first, range.second,
                      [depth, &satelites, &ret](auto const & p) {
                          ret += count_orbits(satelites, p.second, depth + 1);
                      });
        ret += depth;
        return ret;
    }
} // namespace aoc

namespace
{
    std::vector<std::string> build_path(aoc::SolarSystem const & solar_system,
                                        std::string const & node)
    {
        std::vector<std::string> ret;
        auto const e = std::end(solar_system);
        auto it = solar_system.find(node);
        while(it != e)
        {
            ret.insert(std::begin(ret), it->second);
            it = solar_system.find(it->second);
        }
        return ret;
    }
} // namespace

namespace aoc
{
    std::size_t count_hops(SolarSystem const & solar_system,
                           std::string const & first,
                           std::string const & second)
    {
        auto const first_path = build_path(solar_system, first);
        auto const second_path = build_path(solar_system, second);
        auto const first_e = std::end(first_path);
        auto const unique_nodes = std::mismatch(std::begin(first_path), first_e,
                                                std::begin(second_path));

        auto const first_unique = std::distance(unique_nodes.first, first_e);
        auto const second_unique =
            std::distance(unique_nodes.second, std::end(second_path));
        return first_unique + second_unique;
    }
} // namespace aoc
