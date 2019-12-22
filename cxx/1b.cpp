#include <cassert>
#include <fstream>
#include <iostream>

namespace
{
    constexpr auto calculate_fuel_cost(int mass)
    {
        assert(mass >= 0);
        auto const result = (mass / 3) - 2;
        return result;
    }

    auto do_work(std::istream & input)
    {
        int value;
        auto fuel_total = 0;
        while(input >> value)
        {
            auto module_fuel = calculate_fuel_cost(value);
            fuel_total += module_fuel;
            // calculate the fuel's fuel
            module_fuel = calculate_fuel_cost(module_fuel);
            while(module_fuel >= 0)
            {
                fuel_total += module_fuel;
                module_fuel = calculate_fuel_cost(module_fuel);
            }
        }
        return fuel_total;
    }
} // namespace

int main(int argc, char ** argv)
{
    auto fuel_total = [argc, argv]() {
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
    std::cout << fuel_total << '\n';
    return 0;
}
