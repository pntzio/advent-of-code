#pragma once

#include <iostream>
#include <filesystem>
#include <charconv>

#include "aoc/io.h"
#include "aoc/problem.h"

namespace d02 {

void part_a(std::filesystem::path input_path) {
    std::string program = aoc::read_file_line(input_path);
    std::cout << program << std::endl;
}

void part_b(std::filesystem::path input_path) {
}

}
