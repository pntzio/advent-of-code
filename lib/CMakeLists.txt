add_library(aoc SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/include/aoc/io.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/aoc/conversion.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/aoc/problem.h
)

set_target_properties(aoc PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED TRUE
    CXX_EXTENSIONS OFF
)

target_include_directories(aoc PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
