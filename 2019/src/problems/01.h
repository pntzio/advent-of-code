#pragma once

#include <span>
#include <iostream>
#include <filesystem>
#include <numeric>

#include "aoc/io.h"

namespace d01 {

std::int32_t fuel_for_mass(std::int32_t mass) {
    return std::max((mass / 3) - 2, 0);
}

std::int32_t total_fuel_for_mass(std::int32_t mass) {
    std::int32_t total = 0;
    std::int32_t last_mass = mass;
    std::int32_t extra_fuel = 0;

    do {
        extra_fuel = fuel_for_mass(last_mass);
        total += extra_fuel;
        last_mass = extra_fuel;
    } while(extra_fuel > 0);

    return total;
}

void part_a(std::filesystem::path input_path) {
    std::vector<std::uint32_t> numbers = aoc::read_file_lines<std::uint32_t>(input_path);

    std::uint32_t fuel_required = std::accumulate(numbers.cbegin(), numbers.cend(), 0, [](std::uint32_t a, std::uint32_t b) {
        return a + ((b / 3) - 2);
    });

    std::cout << fuel_required << std::endl;
}

void part_b(std::filesystem::path input_path) {
    std::vector<std::int32_t> numbers = aoc::read_file_lines<std::int32_t>(input_path);

    std::int32_t fuel_required = std::accumulate(numbers.cbegin(), numbers.cend(), 0, [](std::int32_t a, std::int32_t b) {
        return a + total_fuel_for_mass(b);
    });

    std::cout << fuel_required << std::endl;
}

}
