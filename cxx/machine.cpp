#include <aoc/machine.hpp>

#include <algorithm>
#include <cassert>
#include <type_traits>

namespace
{
    // helper type shamelessly stolen from cppreference:
    // https://en.cppreference.com/w/cpp/utility/variant/visit
    template <class T>
    struct always_false : std::false_type
    {
    };

    template <typename BINARY_OP>
    aoc::results::Advance binary_op(aoc::Memory::const_iterator instruction,
                                    aoc::Memory & state, BINARY_OP fn)
    {
        auto const a = std::next(instruction, 1);
        auto const b = std::next(instruction, 2);
        auto const c = std::next(instruction, 3);
        state[*c] = fn(state[*a], state[*b]);
        return aoc::results::Advance{4};
    }

    namespace opcode_implementations
    {
        aoc::InstructionResult add(aoc::Memory::const_iterator instruction,
                                   aoc::Memory & state)
        {
            return binary_op(instruction, state, std::plus<void>{});
        }

        aoc::InstructionResult mul(aoc::Memory::const_iterator instruction,
                                   aoc::Memory & state)
        {
            return binary_op(instruction, state, std::multiplies<void>{});
        }

        aoc::InstructionResult
        exit_program(aoc::Memory::const_iterator instruction,
                     aoc::Memory & state)
        {
            (void)instruction;
            (void)state;
            return aoc::results::Halt{};
        }
    } // namespace opcode_implementations
} // namespace

namespace aoc
{

    OpcodeTable::OpcodeTable(std::vector<OpcodeEntry> opcodes)
      : opcode_table{std::move(opcodes)}
    {
        auto compare_fn = [](auto const & lhs, auto const & rhs) {
            return lhs.first < rhs.first;
        };
        assert(std::is_sorted(std::begin(opcode_table), std::end(opcode_table),
                              compare_fn));
    }

    OpcodeTable const & basic_opcodes()
    {
        static OpcodeTable const opcode_table{
            {std::make_pair(1, opcode_implementations::add),
             std::make_pair(2, opcode_implementations::mul),
             std::make_pair(99, opcode_implementations::exit_program)}};

        return opcode_table;
    }

    Machine::Machine(Memory memory, OpcodeTable const & opcodes)
      : state{std::move(memory)}
      , opcode_table{opcodes}
    {
    }

    void Machine::run()
    {
        auto const opcode_table_b = std::begin(opcode_table.opcode_table);
        auto const opcode_table_e = std::end(opcode_table.opcode_table);

        auto current_instruction = std::begin(state);
        auto run = true;
        while(run)
        {
            auto opcode_fn = std::lower_bound(
                opcode_table_b, opcode_table_e, *current_instruction,
                [](auto opcode_entry, auto const & opcode_value) {
                    return opcode_entry.first < opcode_value;
                });
            if((opcode_fn != opcode_table_e) &&
               (opcode_fn->first == *current_instruction))
            {
                auto opcode_result =
                    opcode_fn->second(current_instruction, state);
                std::visit(
                    [&run, &current_instruction](auto const & result) {
                        using T = std::decay_t<decltype(result)>;
                        if constexpr(std::is_same_v<T, results::Advance>)
                        {
                            std::advance(current_instruction, result.count);
                        }
                        else if constexpr(std::is_same_v<T, results::Halt>)
                        {
                            run = false;
                        }
                        else
                        {
                            static_assert(always_false<T>::value,
                                          "non-exhaustive visitor!");
                        }
                    },
                    opcode_result);
            }
            else
            {
                throw std::runtime_error{"Unexpected opcode"};
            }
        }
    }
} // namespace aoc
