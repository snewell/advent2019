#include <algorithm>
#include <array>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>

namespace
{
    std::vector<int> load_program()
    {
        std::vector<int> state;
        int value;
        char dummy;
        while(std::cin >> value)
        {
            state.push_back(value);
            std::cin >> dummy;
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

int main()
{
    auto const default_state = load_program();

    std::array<std::pair<int, std::function<bool(std::vector<int> &,
                                                 std::vector<int>::iterator)>>,
               3> const op_table = {std::make_pair(1, add),
                                    std::make_pair(2, mul),
                                    std::make_pair(99, exit_program)};

    auto const opcode_table_b = std::begin(op_table);
    auto const opcode_table_e = std::end(op_table);

    for(auto noun = 0; noun < 100; ++noun)
    {
        for(auto verb = 0; verb < 100; ++verb)
        {
            try
            {
                auto state = default_state;
                state[1] = noun;
                state[2] = verb;
                auto current_opcode = std::begin(state);
                auto run = true;
                while(run)
                {
                    auto opcode_fn = std::lower_bound(
                        opcode_table_b, opcode_table_e, *current_opcode,
                        [](auto opcode_entry, auto const & opcode_value) {
                            return opcode_entry.first < opcode_value;
                        });
                    if((opcode_fn == opcode_table_e) ||
                       (opcode_fn->first != *current_opcode))
                    {
                        throw std::runtime_error{"Invalid opcode"};
                    }
                    run = opcode_fn->second(state, current_opcode);
                    if(run)
                    {
                        std::advance(current_opcode, 4);
                    }
                }
                // std::cout << noun << '/' << verb << " = " << state.front() <<
                // '\n';
                if(state.front() == 19690720)
                {
                    std::cout << "noun = " << noun << " verb = " << verb
                              << '\n';
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
}
