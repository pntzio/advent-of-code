#pragma once

#include <span>
#include <iostream>
#include <filesystem>

#include "aoc/io.h"

namespace d01 {

struct window {
    using value_type = std::uint32_t;
    using container = std::vector<value_type>;
    using const_iterator = typename container::const_iterator;
    using iterator = const_iterator;

    window(container const& container, typename container::difference_type offset = 0)
    {
        a = std::next(std::cbegin(container), offset);
        b = std::next(a);
        c = std::next(b);
    }

    window& operator=(window const& other) = default;

    value_type value() const {
        return *a + *b + *c;
    }

    void operator++(int) { a++; b++; c++; }

    bool operator<(window const& other) {
        return value() < other.value();
    }

    bool at_end(container const& cont) {
        return c == std::cend(cont);
    }

    iterator a;
    iterator b;
    iterator c;
};

void part_a(std::filesystem::path input_path) {
    std::vector<std::uint32_t> numbers = aoc::read_file_lines<std::uint32_t>(input_path);

    std::uint32_t increases = 0;

    for(auto it = std::next(std::cbegin(numbers)); it != std::cend(numbers); it++) {
        if(*std::prev(it) < *it) {
            increases++;
        }
    }

    std::cout << increases << std::endl;
}

void part_b(std::filesystem::path input_path) {
    std::vector<std::uint32_t> numbers = aoc::read_file_lines<std::uint32_t>(input_path);

    window window_a(numbers);
    window window_b(numbers, 1);

    std::uint32_t increases = 0;

    while(window_b.at_end(numbers) == false) {
        if(window_a < window_b) {
            increases++;
        }

        window_a++;
        window_b++;
    }

    std::cout << increases << std::endl;
}

}
