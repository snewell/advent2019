cmake_minimum_required(VERSION 3.14)
cmake_policy(VERSION 3.14)
project("advent-2019"
    LANGUAGES
        CXX
)

enable_testing()

set(input_dir "${CMAKE_CURRENT_SOURCE_DIR}/../input")

function(create_puzzle name)
    set(options "")
    set(one_value_args VALIDATE)
    set(multi_value_args LIBRARIES SOURCES)
    cmake_parse_arguments(CREATE_PUZZLE "${options}" "${one_value_args}" "${multi_value_args}" ${ARGN})
    add_executable(${name}
        ${name}.cpp
        ${CREATE_PUZZLE_SOURCES}
    )
    if(CREATE_PUZZLE_LIBRARIES)
        target_link_libraries(${name}
            PRIVATE ${CREATE_PUZZLE_LIBRARIES}
        )
    endif()
    target_compile_features(${name} PRIVATE
        cxx_std_17
    )
    set_target_properties(${name} PROPERTIES
        CXX_EXTENSIONS OFF
    )
    add_custom_target(${name}-test
        DEPENDS ${name}
        COMMAND $<TARGET_FILE:${name}> <"${input_dir}/${name}"
    )
    if(CREATE_PUZZLE_VALIDATE)
        set(validate_test "${name}-validate")
        add_test(${validate_test}
            ${name} "${input_dir}/${name}"
        )
        set_tests_properties(${name}-validate PROPERTIES
            PASS_REGULAR_EXPRESSION "${CREATE_PUZZLE_VALIDATE}"
        )
    endif()
endfunction()

function(create_library name)
    add_library(${name} SHARED ${ARGN})
    target_include_directories(${name}
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    )
    set_target_properties(${name} PROPERTIES
        CXX_EXTENSIONS OFF
    )
    target_compile_features(${name} PUBLIC
        cxx_std_17
    )
endfunction()

create_library(machine
    machine.cpp
)
create_library(orbit
    orbit.cpp
)
create_library(segment
    point.cpp
    segment.cpp
    wire.cpp
)
create_library(password
    password.cpp
)

add_subdirectory(test)

create_puzzle(1a
    VALIDATE 3285627
)
create_puzzle(1b
    VALIDATE 4925580
)
create_puzzle(2a
    LIBRARIES
        machine
    VALIDATE 3760627
)
create_puzzle(2b
    LIBRARIES
        machine
    VALIDATE 7195
)
create_puzzle(3a
    LIBRARIES
        segment
    VALIDATE 227
)
create_puzzle(3b
    LIBRARIES
        segment
)
create_puzzle(4a
    LIBRARIES
        password
)
create_puzzle(5a
    LIBRARIES
        machine
    VALIDATE 7566643
)
create_puzzle(5b
    LIBRARIES
        machine
    VALIDATE 9265694
)
create_puzzle(6a
    LIBRARIES
        orbit
    VALIDATE 234446
)
create_puzzle(6b
    LIBRARIES
        orbit
    VALIDATE 385
)
create_puzzle(7a
    LIBRARIES
        machine
    VALIDATE 19650
)
create_puzzle(7b
    LIBRARIES
        machine
    VALIDATE 35961106
)
