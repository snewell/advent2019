#ifndef AOC_MACHINE_HPP
#define AOC_MACHINE_HPP 1

#include <functional>
#include <variant>
#include <vector>

namespace aoc
{
    using Memory = std::vector<int>;

    namespace results
    {
        struct Halt
        {
        };
        struct Advance
        {
            int count;
        };
    } // namespace results

    using InstructionResult = std::variant<results::Halt, results::Advance>;

    struct OpcodeTable
    {
        using OpcodeFn =
            std::function<InstructionResult(Memory::const_iterator, Memory &)>;
        using OpcodeEntry = std::pair<int, OpcodeFn>;

        OpcodeTable(std::vector<OpcodeEntry> opcodes);

        std::vector<OpcodeEntry> opcode_table;
    };

    OpcodeTable const & basic_opcodes();

    struct Machine
    {
        Machine(Memory memory, OpcodeTable const & opcodes);

        void run();

        Memory state;
        OpcodeTable const & opcode_table;
    };
} // namespace aoc

#endif
