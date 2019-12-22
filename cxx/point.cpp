#include <aoc/point.hpp>

namespace
{
    std::size_t axis_distance(int a, int b)
    {
        if((a >= 0) && (b >= 0))
        {
            return a + b;
        }
        else if((a < 0) && (b < 0))
        {
            return std::abs(a + b);
        }
        else
        {
            if(a < b)
            {
                return std::abs(a - b);
            }
            else
            {
                return std::abs(b - a);
            }
        }
    }
} // namespace

namespace aoc
{
    bool operator==(Point lhs, Point rhs) noexcept
    {
        return (lhs.x == rhs.x) && (lhs.y == rhs.y);
    }

    bool operator!=(Point lhs, Point rhs) noexcept
    {
        return (lhs.x != rhs.x) || (lhs.y != rhs.y);
    }

    bool operator<(Point lhs, Point rhs) noexcept
    {
        if(lhs.x < rhs.x)
        {
            return true;
        }
        else if(lhs.x == rhs.x)
        {
            return lhs.y > rhs.y;
        }
        else
        {
            return false;
        }
    }

    std::size_t distance(Point first, Point second) noexcept
    {
        auto const distance_x = axis_distance(first.x, second.x);
        auto const distance_y = axis_distance(first.y, second.y);
        return distance_x + distance_y;
    }
} // namespace aoc
