#include <fstream>
#include <iostream>

#include <aoc/password.hpp>

namespace
{
    std::pair<std::string, std::string> read_min_max(std::istream & istream)
    {
        std::string min;
        std::string max;

        istream >> min >> max;
        return std::make_pair(min, max);
    }
} // namespace

int main(int argc, char ** argv)
{
    auto const [input_min, input_max] = [argc, argv]() {
        if(argc == 1)
        {
            return read_min_max(std::cin);
        }
        else
        {
            std::ifstream input{argv[1]};
            return read_min_max(input);
        }
    }();

    auto const real_min = aoc::raise_floor(input_min);
    auto const real_max = aoc::lower_ceiling(input_max);

    std::cout << real_min << ' ' << real_max << '\n';

    return 0;
}
