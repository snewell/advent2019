cmake_minimum_required(VERSION 3.14)
cmake_policy(VERSION 3.14)
project("advent-2019"
    LANGUAGES
        CXX
)

set(input_dir "${CMAKE_CURRENT_SOURCE_DIR}/../input")

function(create_puzzle name)
    add_executable(${name}
        ${name}.cpp
        ${ARGN}
    )
    set_target_properties(${name} PROPERTIES
        CXX_EXTENSIONS OFF
    )
    target_compile_features(${name} PRIVATE
        cxx_std_17
    )

    add_custom_target(${name}-test
        DEPENDS ${name}
        COMMAND $<TARGET_FILE:${name}> <"${input_dir}/${name}"
    )
endfunction()

create_puzzle(1a)
create_puzzle(1b)
