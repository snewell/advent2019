#ifndef AOC_MACHINE_HPP
#define AOC_MACHINE_HPP 1

#include <functional>
#include <istream>
#include <ostream>
#include <variant>
#include <vector>

namespace aoc
{
    using Memory = std::vector<int>;

    struct Io
    {
        std::istream & input;
        std::ostream & output;
    };

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
        using OpcodeFn = std::function<InstructionResult(
            Memory::const_iterator, Memory &, Io const & io)>;
        using OpcodeEntry = std::pair<int, OpcodeFn>;

        OpcodeTable(std::vector<OpcodeEntry> opcodes);

        std::vector<OpcodeEntry> opcode_table;
    };

    OpcodeTable const & basic_opcodes();

    OpcodeTable const & io_opcodes();

    struct Machine
    {
        Machine(Io io, Memory memory, OpcodeTable const & opcodes);

        void run();

        Io io;
        Memory state;
        OpcodeTable const & opcode_table;
    };
} // namespace aoc

#endif
