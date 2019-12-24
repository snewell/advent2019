#include <aoc/password.hpp>

#include <algorithm>
#include <cassert>

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

    std::size_t count_possible_endings(std::string base,
                                       std::size_t prefix_length)
    {
        // TODO: Figure out a better algorithm.  I'm pretty sure there's an
        // obvious pattern that I'm missing.
        assert(prefix_length > 0);
        if((base.size() - prefix_length) == 1)
        {
            return '9' - base[prefix_length - 1] + 1;
        }
        else if(prefix_length < base.size())
        {
            std::size_t sub = 0;
            while(base[prefix_length] <= '9')
            {
                sub += count_possible_endings(base, prefix_length + 1);
                ++base[prefix_length];
            }
            return sub;
        }
        else
        {
            return 0;
        }
    }
} // namespace aoc
