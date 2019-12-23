#include <aoc/password.hpp>

#include <algorithm>

namespace aoc
{
    std::string raise_floor(std::string const & min)
    {
        auto const b = std::begin(min);
        auto const e = std::end(min);

        auto it = std::adjacent_find(
            b, e, [](auto first, auto second) { return second < first; });
        if(it == e)
        {
            // the original input meets the "only inreasing" requirement
            return min;
        }
        else
        {
            std::string ret;
            ret.reserve(min.size());
            std::copy(b, it, std::back_inserter(ret));
            while(ret.size() < min.size())
            {
                ret.push_back(*it);
            }
            return ret;
        }
    }

    std::string lower_ceiling(std::string const & max)
    {
        auto const b = std::begin(max);
        auto const e = std::end(max);

        auto it = std::adjacent_find(
            b, e, [](auto first, auto second) { return second < first; });
        if(it == e)
        {
            // the original input meets the "only inreasing" requirement
            return max;
        }
        else
        {
            std::string ret;
            ret.reserve(max.size());
            std::copy(b, it, std::back_inserter(ret));
            ret.push_back(*it - 1);
            while(ret.size() < max.size())
            {
                ret.push_back('9');
            }
            return ret;
        }
    }
} // namespace aoc
