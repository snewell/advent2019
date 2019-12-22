cmake_minimum_required(VERSION 3.14)
cmake_policy(VERSION 3.14)
project("advent-2019"
    LANGUAGES
        CXX
)

enable_testing()

set(input_dir "${CMAKE_CURRENT_SOURCE_DIR}/../input")

function(create_puzzle name)
    add_executable(${name}
        ${name}.cpp
        ${ARGN}
    )
    target_link_libraries(${name}
        PRIVATE aoc
    )
    set_target_properties(${name} PROPERTIES
        CXX_EXTENSIONS OFF
    )

    add_custom_target(${name}-test
        DEPENDS ${name}
        COMMAND $<TARGET_FILE:${name}> <"${input_dir}/${name}"
    )
endfunction()

add_library(aoc SHARED
    point.cpp
    segment.cpp
)
target_include_directories(aoc
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
set_target_properties(aoc PROPERTIES
    CXX_EXTENSIONS OFF
)
target_compile_features(aoc PUBLIC
    cxx_std_17
)

add_subdirectory(test)

create_puzzle(1a)
create_puzzle(1b)
create_puzzle(2a)
create_puzzle(2b)
create_puzzle(3a)
