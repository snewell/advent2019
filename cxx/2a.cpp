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
        return aoc::Machine{aoc::Io{input, std::cout}, state,
                            aoc::basic_opcodes()};
    }
} // namespace

int main(int argc, char ** argv)
{
    auto do_work = [](auto machine) {
        machine.run();
        std::cout << machine.state.front() << '\n';
        return 0;
    };
    return [argc, argv, do_work]() {
        if(argc == 1)
        {
            return do_work(load_program(std::cin));
        }
        else
        {
            std::ifstream input{argv[1]};
            return do_work(load_program(input));
        }
    }();
}
