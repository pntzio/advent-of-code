#pragma once

#include <iostream>
#include <filesystem>

#include "aoc/io.h"
#include "aoc/problem.h"

namespace y21d02 {

std::string_view get_direction(std::string const& str) {
    std::string_view result(str);
    std::size_t space_index = result.find_first_of(' ');

    return result.substr(0, space_index);
}

std::int32_t get_count(std::string const& str) {
    std::size_t space_index = str.find_last_of(' ');
    return std::stol(str.substr(space_index));
}

void part_a(std::filesystem::path input_path) {
    std::vector<std::string> input_lines = aoc::read_file_lines<std::string>(input_path);

    std::int32_t x = 0;
    std::int32_t y = 0;

    for(std::string const& line : input_lines) {
        std::int32_t steps = get_count(line);
        std::string_view instruction = get_direction(line);

        if(instruction == "forward") {
            x += steps;
        } else if(instruction == "down") {
            y += steps;
        } else if(instruction == "up") {
            y -= steps;
        }
    }

    std::cout << x * y << std::endl;

}

void part_b(std::filesystem::path input_path) {
    std::vector<std::string> input_lines = aoc::read_file_lines<std::string>(input_path);

    std::int32_t x = 0;
    std::int32_t y = 0;
    std::int32_t aim = 0;

    for(std::string const& line : input_lines) {
        std::int32_t steps = get_count(line);
        std::string_view instruction = get_direction(line);

        if(instruction == "forward") {
            x += steps;
            y += (aim * steps);
        } else if(instruction == "down") {
            aim += steps;
        } else if(instruction == "up") {
            aim -= steps;
        }
    }

    std::cout << x * y << std::endl;
}

}
