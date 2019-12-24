#include <aoc/machine.hpp>

#include <gtest/gtest.h>

TEST(Machine, immediate_example)
{
    aoc::Memory default_memory = {
        1002, // mul, with one immediate argument
        4,    // storage address
        3,    // immediate argument
        4,    // position argument
        33    // value in position argument
    };

    aoc::Machine machine{aoc::Io{std::cin, std::cout}, default_memory,
                         aoc::basic_opcodes()};
    machine.run();
    ASSERT_EQ(99, machine.state[4]);
}

TEST(Machine, immediate_add)
{
    aoc::Memory default_memory = {
        1001, // add, with one immediate argument
        4,    // storage address
        87,   // immediate argument
        4,    // position argument
        12    // value in position argument
    };

    aoc::Machine machine{aoc::Io{std::cin, std::cout}, default_memory,
                         aoc::basic_opcodes()};
    machine.run();
    ASSERT_EQ(99, machine.state[4]);
}
