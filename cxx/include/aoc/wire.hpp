#ifndef AOC_WIRE_HPP
#define AOC_WIRE_HPP 1

#include <aoc/segment.hpp>

namespace aoc
{
    struct Wire
    {
        void add_segment(aoc::Segment segment);

        std::vector<aoc::Segment> horizontal;
        std::vector<aoc::Segment> vertical;
    };
} // namespace aoc

#endif
