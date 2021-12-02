#pragma once

#include <iostream>
#include <filesystem>
#include <charconv>

#include "aoc/io.h"
#include "aoc/problem.h"

namespace d02 {

struct instruction {

    static instruction from_string(std::string_view str) {
        instruction result;

        std::string_view direction_str = str.substr(0, str.find_first_of(' '));
        str.remove_prefix(direction_str.size());
        std::string_view magnitude_str = str.substr(1);

        if(direction_str == "forward") { result.dir = direction::forward; }
        else if(direction_str == "down") { result.dir = direction::down; }
        else if(direction_str == "up") { result.dir = direction::up; }

        std::from_chars(magnitude_str.data(), magnitude_str.data() + magnitude_str.size(), result.magnitude);

        return result;
    }

    enum class direction {
        up,
        down,
        forward
    };

    direction    dir;
    std::int32_t magnitude;
};

void part_a(std::filesystem::path input_path) {
    std::vector<std::string> input_lines = aoc::read_file_lines(input_path);

    std::int32_t x = 0;
    std::int32_t y = 0;

    for(std::string_view line : input_lines) {
        instruction inst = instruction::from_string(line);

        switch(inst.dir) {
            case instruction::direction::forward: x += inst.magnitude; break;
            case instruction::direction::down: y += inst.magnitude; break;
            case instruction::direction::up: y -= inst.magnitude; break;
        }
    }

    std::cout << x * y << std::endl;

}

void part_b(std::filesystem::path input_path) {
    std::vector<std::string> input_lines = aoc::read_file_lines(input_path);

    std::int32_t x = 0;
    std::int32_t y = 0;
    std::int32_t aim = 0;

    for(std::string_view line : input_lines) {
        instruction inst = instruction::from_string(line);

        switch(inst.dir) {
            case instruction::direction::forward:
            {
                x += inst.magnitude;
                y += (aim * inst.magnitude);
                break;
            }
            case instruction::direction::down: aim += inst.magnitude; break;
            case instruction::direction::up: aim -= inst.magnitude; break;
        }
    }

    std::cout << x * y << std::endl;
}

}
