#include <fstream>
#include <iostream>

#include <aoc/machine.hpp>

namespace
{
    aoc::Memory load_program(std::istream & input)
    {
        aoc::Memory state;
        int value;
        char dummy;
        while(input >> value)
        {
            state.push_back(value);
            input >> dummy;
        }
        return state;
    }
} // namespace

int main(int argc, char ** argv)
{
    auto do_work = [](auto default_state, auto & input) {
        for(auto noun = 0; noun < 100; ++noun)
        {
            for(auto verb = 0; verb < 100; ++verb)
            {
                try
                {
                    aoc::Machine machine{aoc::Io{input, std::cout},
                                         default_state, aoc::basic_opcodes()};
                    machine.state[1] = noun;
                    machine.state[2] = verb;
                    machine.run();
                    if(machine.state.front() == 19690720)
                    {
                        std::cout << 100 * noun + verb << '\n';
                        return 0;
                    }
                }
                catch(...)
                {
                    // swallow exception for now
                }
            }
        }
        std::cerr << "Cannot find solution\n";
        return 1;
    };

    return [argc, argv, do_work]() {
        if(argc == 1)
        {
            return do_work(load_program(std::cin), std::cin);
        }
        else
        {
            std::ifstream input{argv[1]};
            return do_work(load_program(input), input);
        }
    }();
}
