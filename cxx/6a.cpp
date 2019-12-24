#include <fstream>
#include <iostream>

#include <aoc/orbit.hpp>

int main(int argc, char ** argv)
{
    auto do_work = [](auto & input) {
        auto const solar_system = aoc::parse_satelites(input);
        auto const count = aoc::count_orbits(solar_system, "COM");
        std::cout << count << '\n';
        return 0;
    };
    return [argc, argv, do_work]() {
        if(argc == 1)
        {
            return do_work(std::cin);
        }
        else
        {
            std::ifstream input{argv[1]};
            return do_work(input);
        }
    }();
}
