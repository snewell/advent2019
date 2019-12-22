#include <aoc/wire.hpp>

#include <algorithm>
#include <cassert>

namespace
{
    void add_segment_helper(std::vector<aoc::Segment> & segments,
                            aoc::Segment segment)
    {
        auto it =
            std::upper_bound(std::begin(segments), std::end(segments), segment);
        segments.insert(it, segment);
    }
} // namespace

namespace aoc
{
    void Wire::add_segment(aoc::Segment segment)
    {
        if(segment.first.y == segment.second.y)
        {
            // horizontal
            add_segment_helper(horizontal, segment);
        }
        else
        {
            // vertical
            assert(segment.first.x == segment.second.x);
            add_segment_helper(vertical, segment);
        }
    }
} // namespace aoc
