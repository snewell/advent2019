#include <cassert>
#include <iostream>

namespace
{
    constexpr auto calculate_fuel_cost(int mass)
    {
        assert(mass >= 0);
        auto const result = (mass / 3) - 2;
        return result;
    }
} // namespace

int main()
{
    int input;
    auto fuel_total = 0;
    while(std::cin >> input)
    {
        auto module_fuel = calculate_fuel_cost(input);
        fuel_total += module_fuel;
        // calculate the fuel's fuel
        module_fuel = calculate_fuel_cost(module_fuel);
        while(module_fuel >= 0)
        {
            fuel_total += module_fuel;
            module_fuel = calculate_fuel_cost(module_fuel);
        }
    }
    std::cout << fuel_total << '\n';
    return 0;
}
