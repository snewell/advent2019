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
    set(one_value_args "")
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
endfunction()

add_library(segment SHARED
    point.cpp
    segment.cpp
    wire.cpp
)
target_include_directories(segment
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
set_target_properties(segment PROPERTIES
    CXX_EXTENSIONS OFF
)
target_compile_features(segment PUBLIC
    cxx_std_17
)

add_subdirectory(test)

create_puzzle(1a)
create_puzzle(1b)
create_puzzle(2a)
create_puzzle(2b)
create_puzzle(3a
    LIBRARIES
        segment
)
