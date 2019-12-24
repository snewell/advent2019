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

    auto make_input(int phase, int input)
    {
        std::ostringstream os;
        os << phase << ' ' << input;
        return os.str();
    }

    auto extract_output(std::string const & output)
    {
        std::istringstream reader{output};
        int result;
        reader >> result;
        return result;
    }

    int run_permutation(aoc::Memory const & initial_state,
                        std::vector<int> const & phases)
    {
        auto last_output = 0;
        std::for_each(
            std::begin(phases), std::end(phases),
            [&initial_state, &last_output](auto phase) {
                std::istringstream input{make_input(phase, last_output)};
                std::ostringstream output;

                aoc::Machine machine{aoc::Io{input, output}, initial_state,
                                     aoc::io_opcodes()};
                machine.run();
                last_output = extract_output(output.str());
            });
        return last_output;
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

    std::vector<int> phases{0, 1, 2, 3, 4};
    auto max_output = std::numeric_limits<int>::min();
    do
    {
        auto const output = run_permutation(default_state, phases);
        max_output = std::max(max_output, output);
    } while(std::next_permutation(std::begin(phases), std::end(phases)));
    std::cout << max_output << '\n';
    return 0;
}
