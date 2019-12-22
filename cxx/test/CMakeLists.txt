find_package(GTest CONFIG REQUIRED)

function(create_test name)
    add_executable(${name} ${ARGN})
    set_target_properties(${name} PROPERTIES
        CXX_EXTENSIONS OFF
    )
    target_link_libraries(${name}
        PRIVATE aoc
        PRIVATE GTest::gtest
        PRIVATE GTest::gtest_main
    )
    add_test(${name} ${name})
endfunction()

create_test(segment
    point_test.cpp
    segment_test.cpp
)
