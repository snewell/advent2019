#include <fstream>
#include <iostream>

#include <aoc/machine.hpp>

namespace
{
    aoc::Machine load_program(std::istream & input)
    {
        aoc::Memory state;
        int value;
        char dummy;
        while(input >> value)
        {
            state.push_back(value);
            input >> dummy;
        }
        return aoc::Machine{state, aoc::basic_opcodes()};
    }
} // namespace

int main(int argc, char ** argv)
{
    auto machine = [argc, argv]() {
        if(argc == 1)
        {
            return load_program(std::cin);
        }
        else
        {
            std::ifstream input{argv[1]};
            return load_program(input);
        }
    }();

    machine.run();
    std::cout << machine.state.front() << '\n';
    return 0;
}
