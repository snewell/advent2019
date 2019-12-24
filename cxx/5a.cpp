#include <fstream>
#include <iostream>

#include <aoc/machine.hpp>

namespace
{
    aoc::Machine load_program(std::istream & input)
    {
        aoc::Memory state;
        int value;
        auto dummy = 'a';
        while((dummy != '\n') && (input >> value))
        {
            state.push_back(value);
            input.get(dummy);
        }
        return aoc::Machine{aoc::Io{input, std::cout}, state,
                            aoc::io_opcodes()};
    }
} // namespace

int main(int argc, char ** argv)
{
    auto do_work = [](auto machine) {
        machine.run();
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
