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

    bool test_position(int instruction_value, int position_test)
    {
        auto const trimmed = instruction_value / position_test;
        return (trimmed % 10);
    }

    template <typename BINARY_OP>
    aoc::results::Advance binary_op(aoc::Memory::const_iterator instruction,
                                    aoc::Memory & state, aoc::Io const & io,
                                    BINARY_OP fn)
    {
        (void)io;
        auto const immediate_first = test_position(*instruction, 100);
        auto const immediate_second = test_position(*instruction, 1000);
        auto const immediate_third = test_position(*instruction, 10000);
        assert(!immediate_third);
        auto const a = std::next(instruction, 1);
        auto const b = std::next(instruction, 2);
        auto const c = std::next(instruction, 3);
        state[*c] = fn(immediate_first ? *a : state[*a],
                       immediate_second ? *b : state[*b]);
        return aoc::results::Advance{4};
    }

    namespace opcode_implementations
    {
        aoc::InstructionResult add(aoc::Memory::const_iterator instruction,
                                   aoc::Memory & state, aoc::Io const & io)
        {
            return binary_op(instruction, state, io, std::plus<void>{});
        }

        aoc::InstructionResult mul(aoc::Memory::const_iterator instruction,
                                   aoc::Memory & state, aoc::Io const & io)
        {
            return binary_op(instruction, state, io, std::multiplies<void>{});
        }

        aoc::InstructionResult read_int(aoc::Memory::const_iterator instruction,
                                        aoc::Memory & state, aoc::Io const & io)
        {
            auto address = std::next(instruction, 1);
            assert(io.input);
            io.input >> state[*address];
            assert(io.input);
            return aoc::results::Advance{2};
        }

        aoc::InstructionResult
        print_int(aoc::Memory::const_iterator instruction, aoc::Memory & state,
                  aoc::Io const & io)
        {
            auto address = std::next(instruction, 1);
            io.output << state[*address] << '\n';
            return aoc::results::Advance{2};
        }

        aoc::InstructionResult
        exit_program(aoc::Memory::const_iterator instruction,
                     aoc::Memory & state, aoc::Io const & io)
        {
            (void)instruction;
            (void)state;
            (void)io;
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

    OpcodeTable const & io_opcodes()
    {
        static OpcodeTable const opcode_table{
            {std::make_pair(1, opcode_implementations::add),
             std::make_pair(2, opcode_implementations::mul),
             std::make_pair(3, opcode_implementations::read_int),
             std::make_pair(4, opcode_implementations::print_int),
             std::make_pair(99, opcode_implementations::exit_program)}};

        return opcode_table;
    }

    Machine::Machine(Io io, Memory memory, OpcodeTable const & opcodes)
      : io{io}
      , state{std::move(memory)}
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
            auto const current_opcode = *current_instruction % 100;
            auto opcode_fn = std::lower_bound(
                opcode_table_b, opcode_table_e, current_opcode,
                [](auto opcode_entry, auto const & opcode_value) {
                    return opcode_entry.first < opcode_value;
                });
            if((opcode_fn != opcode_table_e) &&
               (opcode_fn->first == current_opcode))
            {
                auto opcode_result =
                    opcode_fn->second(current_instruction, state, io);
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
