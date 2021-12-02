add_executable(runner
    src/main.cpp
)

set_target_properties(runner PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED TRUE
    CXX_EXTENSIONS OFF
)

target_link_libraries(runner PUBLIC aoc)

file(COPY inputs DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
