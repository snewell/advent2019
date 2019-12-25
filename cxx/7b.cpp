#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>

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

    int run_permutation(aoc::Memory const & initial_state,
                        std::vector<int> const & phases)
    {
        std::vector<std::stringstream> inputs;
        std::vector<std::stringstream> outputs;
        std::vector<aoc::Machine> machines;

        inputs.resize(phases.size());
        outputs.resize(phases.size());
        machines.reserve(phases.size());
        for(std::size_t i = 0; i < phases.size(); ++i)
        {
            machines.emplace_back(aoc::Io{inputs[i], outputs[i]}, initial_state,
                                  aoc::io_opcodes());
            inputs[i] << phases[i] << '\n';
        }
        // seed initial phase
        inputs[0] << 0 << '\n';
        while(true)
        {
            for(std::size_t i = 0; i < phases.size(); ++i)
            {
                auto feed = [i, &inputs, &outputs]() {
                    auto const next = (i + 1) % inputs.size();
                    inputs[next].clear();
                    int temp;
                    while(outputs[i] >> temp)
                    {
                        inputs[next] << temp << '\n';
                    }
                    outputs[i].clear();
                };
                try
                {
                    machines[i].run();
                    if(i == (phases.size() - 1))
                    {
                        // last machine terminated cleanly, so return it's value
                        int temp;
                        outputs[i] >> temp;
                        return temp;
                    }
                    else
                    {
                        feed();
                    }
                }
                catch(...)
                {
                    feed();
                }
            }
        }
    }
} // namespace

int main(int argc, char ** argv)
{
    auto default_state = [argc, argv]() {
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

    std::vector<int> phases{5, 6, 7, 8, 9};
    auto max_output = std::numeric_limits<int>::min();
    do
    {
        auto const output = run_permutation(default_state, phases);
        std::cout << "Result = " << output << '\n';
        max_output = std::max(max_output, output);
    } while(std::next_permutation(std::begin(phases), std::end(phases)));
    std::cout << max_output << '\n';
    return 0;
}
