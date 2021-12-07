#pragma once

#include <iostream>
#include <bitset>
#include <filesystem>

#include "aoc/io.h"

namespace d03 {

std::uint8_t most_common_bit(std::vector<std::string> const& lines, std::size_t index) {
    std::size_t ones = 0;
    std::size_t zeros = 0;

    for(std::string_view str : lines) {
        if(str[index] == '1') {
            ones++;
        } else {
            zeros++;
        }
    }

    if(ones == zeros) {
        return 0;
    }

    return ones > zeros ? 1 : 0;
}

std::uint8_t least_common_bit(std::vector<std::string> const& lines, std::size_t index) {
    return most_common_bit(lines, index) == 1 ? 0 : 1;
}

template <std::size_t N>
std::uint16_t most_common_bit2(std::vector<std::bitset<N>> const& numbers, std::size_t index) {
    auto ones = std::count_if(std::cbegin(numbers), std::cend(numbers), [=](std::bitset<N> const& bits) {
        return bits.test(index);
    });

    return ones >= (numbers.size() / 2) ? 1 : 0;
}

void part_a(std::filesystem::path input_path) {
    std::vector<std::bitset<16>> input = aoc::read_file_lines<std::bitset<16>>(input_path);
    std::cout << most_common_bit2(input, 0) << std::endl;
    /*std::vector<std::string> input_lines = aoc::read_file_lines(input_path);
    std::bitset<12> gamma_bits;
    std::bitset<12> epsilon_bits;

    for(std::size_t i = 0; i < input_lines[0].size(); i++) {
        gamma_bits.set(11 - i, most_common_bit(input_lines, i));
    }

    epsilon_bits = gamma_bits;
    epsilon_bits.flip();

    auto gamma = gamma_bits.to_ulong();
    auto epsilon = epsilon_bits.to_ulong();

    std::cout << gamma * epsilon << std::endl;*/
}

std::string reduce_by_most_bit_commonality(std::vector<std::string> bits, std::uint8_t tie_bit = 0) {
    std::size_t num_bits = bits.back().size();

    for(std::size_t i = 0; i < num_bits; i++) {
        std::size_t zeros = std::count_if(bits.cbegin(), bits.cend(), [&](std::string const& str) {
            return str[i] == '0';
        });
        std::size_t ones = std::count_if(bits.cbegin(), bits.cend(), [&](std::string const& str) {
            return str[i] == '1';
        });

        if(zeros > ones) {
            // Remove all lines with ones at pos i
            bits.erase(std::remove_if(bits.begin(), bits.end(), [&](std::string const& str) {
                return str[i] == '1';
            }), bits.end());
        } else if(zeros <= ones) {
            // Remove all lines with zeros at pos i
            bits.erase(std::remove_if(bits.begin(), bits.end(), [&](std::string const& str) {
                return str[i] == '0';
            }), bits.end());
        }

        if(bits.size() == 1) {
            break;
        }
    }

    return bits[0];
}

std::string reduce_by_least_bit_commonality(std::vector<std::string> bits, std::uint8_t tie_bit = 0) {
    std::size_t num_bits = bits.back().size();

    for(std::size_t i = 0; i < num_bits; i++) {
        std::size_t zeros = std::count_if(bits.cbegin(), bits.cend(), [&](std::string const& str) {
            return str[i] == '0';
        });
        std::size_t ones = std::count_if(bits.cbegin(), bits.cend(), [&](std::string const& str) {
            return str[i] == '1';
        });

        if(zeros > ones) {
            // Remove all lines with ones at pos i
            bits.erase(std::remove_if(bits.begin(), bits.end(), [&](std::string const& str) {
                return str[i] == '0';
            }), bits.end());
        } else if(zeros <= ones) {
            // Remove all lines with zeros at pos i
            bits.erase(std::remove_if(bits.begin(), bits.end(), [&](std::string const& str) {
                return str[i] == '1';
            }), bits.end());
        }

        if(bits.size() == 1) {
            break;
        }
    }

    return bits[0];
}

void part_b(std::filesystem::path input_path) {
    std::vector<std::string> input_lines = aoc::read_file_lines(input_path);
    std::string oxygen_rating_bits = reduce_by_most_bit_commonality(input_lines);
    std::string co_srubber_bits = reduce_by_least_bit_commonality(input_lines);

    std::cout << oxygen_rating_bits << std::endl;
    std::cout << co_srubber_bits << std::endl;

    std::bitset<12> ob(oxygen_rating_bits);
    std::bitset<12> cs(co_srubber_bits);

    std::cout << ob.to_ulong() * cs.to_ulong() << std::endl;
}

}
