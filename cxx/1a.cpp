#include <cassert>
#include <fstream>
#include <iostream>

namespace
{
    constexpr auto calculate_fuel_cost(int mass)
    {
        assert(mass >= 0);
        auto const result = (mass / 3) - 2;
        assert(result >= 0);
        return result;
    }

    auto do_work(std::istream & input)
    {
        int value;
        auto total = 0;
        while(input >> value)
        {
            total += calculate_fuel_cost(value);
        }
        return total;
    }

} // namespace

int main(int argc, char ** argv)
{
    auto total = [argc, argv]() {
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
    std::cout << total << '\n';
    return 0;
}
