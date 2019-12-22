#include <algorithm>
#include <array>
#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>

namespace
{
    std::vector<int> load_program(std::istream & input)
    {
        std::vector<int> state;
        int value;
        char dummy;
        while(input >> value)
        {
            state.push_back(value);
            input >> dummy;
        }
        return state;
    }

    template <typename BINARY_OP>
    bool binary_op(std::vector<int> & state, std::vector<int>::iterator opcode,
                   BINARY_OP fn)
    {
        auto const a = std::next(opcode, 1);
        auto const b = std::next(opcode, 2);
        auto const c = std::next(opcode, 3);
        state[*c] = fn(state[*a], state[*b]);
        return true;
    }

    bool add(std::vector<int> & state, std::vector<int>::iterator opcode)
    {
        return binary_op(state, opcode, std::plus<void>{});
    }

    bool mul(std::vector<int> & state, std::vector<int>::iterator opcode)
    {
        return binary_op(state, opcode, std::multiplies<void>{});
    }

    bool exit_program(std::vector<int> & state,
                      std::vector<int>::iterator opcode)
    {
        (void)state;
        (void)opcode;
        return false;
    }
} // namespace

int main(int argc, char ** argv)
{
    auto state = [argc, argv]() {
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

    std::array<std::pair<int, std::function<bool(std::vector<int> &,
                                                 std::vector<int>::iterator)>>,
               3> const op_table = {std::make_pair(1, add),
                                    std::make_pair(2, mul),
                                    std::make_pair(99, exit_program)};

    auto const opcode_table_b = std::begin(op_table);
    auto const opcode_table_e = std::end(op_table);

    auto current_opcode = std::begin(state);
    auto run = true;
    while(run)
    {
        // std::copy(std::begin(state), std::end(state),
        // std::ostream_iterator<int>{std::cout, ","}); std::cout << '\n';
        auto opcode_fn =
            std::lower_bound(opcode_table_b, opcode_table_e, *current_opcode,
                             [](auto opcode_entry, auto const & opcode_value) {
                                 return opcode_entry.first < opcode_value;
                             });
        assert(opcode_fn != opcode_table_e);
        assert(opcode_fn->first == *current_opcode);
        run = opcode_fn->second(state, current_opcode);
        if(run)
        {
            std::advance(current_opcode, 4);
        }
    }
    std::cout << state.front() << '\n';
    return 0;
}
