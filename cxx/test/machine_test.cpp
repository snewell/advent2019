#include <aoc/machine.hpp>

#include <sstream>

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

TEST(Machine, eq_example)
{
    // 3,9,8,9,10,9,4,9,99,-1,8
    aoc::Memory default_memory = {/* 00 */ 3, // read int
                                  /* 01 */ 9, // store result in 9

                                  /* 02 */ 8,  // equality test
                                  /* 03 */ 9,  // address 9
                                  /* 04 */ 10, // address 10
                                  /* 05 */ 9,  // store result in 9

                                  /* 06 */ 4, // ouptut
                                  /* 07 */ 9, // address 9

                                  /* 08 */ 99, // halt
                                  /* 09 */ -1,
                                  /* 10 */ 8};

    {
        std::ostringstream os;
        std::istringstream is{"8"};
        aoc::Machine machine{aoc::Io{is, os}, default_memory,
                             aoc::io_opcodes()};
        machine.run();
        ASSERT_EQ("1\n", os.str());
    }
    {
        std::ostringstream os;
        std::istringstream is{"9"};
        aoc::Machine machine{aoc::Io{is, os}, default_memory,
                             aoc::io_opcodes()};
        machine.run();
        ASSERT_EQ("0\n", os.str());
    }
}

TEST(Machine, lt_example)
{
    // 3,9,8,9,10,9,4,9,99,-1,8
    aoc::Memory default_memory = {/* 00 */ 3, // read int
                                  /* 01 */ 9, // store result in 9

                                  /* 02 */ 7,  // less than test
                                  /* 03 */ 9,  // address 9
                                  /* 04 */ 10, // address 10
                                  /* 05 */ 9,  // store result in 9

                                  /* 06 */ 4, // ouptut
                                  /* 07 */ 9, // address 9

                                  /* 08 */ 99, // halt
                                  /* 09 */ -1,
                                  /* 10 */ 8};

    {
        std::ostringstream os;
        std::istringstream is{"6"};
        aoc::Machine machine{aoc::Io{is, os}, default_memory,
                             aoc::io_opcodes()};
        machine.run();
        ASSERT_EQ("1\n", os.str());
    }
    {
        std::ostringstream os;
        std::istringstream is{"9"};
        aoc::Machine machine{aoc::Io{is, os}, default_memory,
                             aoc::io_opcodes()};
        machine.run();
        ASSERT_EQ("0\n", os.str());
    }
}

TEST(Machine, eq_example_immediate)
{
    // 3,9,8,9,10,9,4,9,99,-1,8
    aoc::Memory default_memory = {
        /* 00 */ 3, // read int
        /* 01 */ 3, // store result in 3

        /* 02 */ 1108, // equality test
        /* 03 */ -1,   // value (should be overwritten)
        /* 04 */ 8,    // value
        /* 05 */ 3,    // store result in 3

        /* 06 */ 4, // ouptut
        /* 07 */ 3, // address 3

        /* 08 */ 99 // halt
    };

    {
        std::ostringstream os;
        std::istringstream is{"8"};
        aoc::Machine machine{aoc::Io{is, os}, default_memory,
                             aoc::io_opcodes()};
        machine.run();
        ASSERT_EQ("1\n", os.str());
    }
    {
        std::ostringstream os;
        std::istringstream is{"9"};
        aoc::Machine machine{aoc::Io{is, os}, default_memory,
                             aoc::io_opcodes()};
        machine.run();
        ASSERT_EQ("0\n", os.str());
    }
}

TEST(Machine, lt_example_immediate)
{
    // 3,9,8,9,10,9,4,9,99,-1,8
    aoc::Memory default_memory = {
        /* 00 */ 3, // read int
        /* 01 */ 3, // store result in 3

        /* 02 */ 1107, // less than test
        /* 03 */ -1,   // value (should be overwritten)
        /* 04 */ 8,    // value
        /* 05 */ 3,    // store result in 3

        /* 06 */ 4, // ouptut
        /* 07 */ 3, // address 3

        /* 08 */ 99 // halt
    };

    {
        std::ostringstream os;
        std::istringstream is{"6"};
        aoc::Machine machine{aoc::Io{is, os}, default_memory,
                             aoc::io_opcodes()};
        machine.run();
        ASSERT_EQ("1\n", os.str());
    }
    {
        std::ostringstream os;
        std::istringstream is{"9"};
        aoc::Machine machine{aoc::Io{is, os}, default_memory,
                             aoc::io_opcodes()};
        machine.run();
        ASSERT_EQ("0\n", os.str());
    }
}

TEST(Machine, resume)
{
    aoc::Memory default_memory = {
        /* 00 */ 3, // read int
        /* 01 */ 2, // store in address 2
        /* 02 */ 0  // dummy address (will be overwritten
    };
    std::stringstream input;
    std::stringstream output;
    aoc::Machine machine{aoc::Io{input, output}, default_memory,
                         aoc::io_opcodes()};

    auto run = [&machine]() { machine.run(); };
    ASSERT_THROW(run(), std::runtime_error);
    input.clear();
    input << 99 << '\n';
    run();
}
