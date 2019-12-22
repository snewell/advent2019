#include <cassert>
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
} // namespace

int main()
{
    int input;
    auto total = 0;
    while(std::cin >> input)
    {
        total += calculate_fuel_cost(input);
    }
    std::cout << total << '\n';
    return 0;
}
