add_executable(aoc-2019
    src/main.cpp
)

set_target_properties(aoc-2019 PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED TRUE
    CXX_EXTENSIONS OFF
)

target_link_libraries(aoc-2019 PUBLIC aoc)

target_include_directories(aoc-2019 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

file(COPY inputs DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
