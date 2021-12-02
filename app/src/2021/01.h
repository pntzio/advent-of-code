#pragma once

#include <filesystem>

#include "aoc/io.h"

namespace y21d01 {

void part_a(std::filesystem::path input_path) {
    std::vector<std::uint32_t> depths = aoc::read_file_lines<std::uint32_t>(input_path);

    std::cout << depths[0] << std::endl;
}

void part_b(std::filesystem::path input_path) {

}

}
