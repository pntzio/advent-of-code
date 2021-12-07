#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

#include "aoc/conversion.h"

namespace aoc {

template <typename T = std::string>
std::vector<T> split_string(std::string_view str, char delimiter = ' ') {
    std::vector<T> result;

    while(!str.empty()) {
        str.remove_prefix(str.find_first_not_of(delimiter));
        std::string_view::size_type index = std::min(str.find_first_of(delimiter), str.length());
        result.push_back(converter<T>()(str.substr(0, index)));
        str.remove_prefix(index);
    }

    return result;
}

template <typename T = std::string>
T read_file_line(std::filesystem::path path) {
    std::ifstream stream(path);
    std::string line;

    std::getline(stream, line);

    return converter<T>()(line);
}

template <typename T = std::string>
std::vector<T> read_file_lines(std::filesystem::path path) {
    std::vector<T> result;
    std::ifstream stream(path);
    std::string line;

    while(std::getline(stream, line)) {
        if(line.empty()) {
            continue;
        }
        result.push_back(converter<T>()(line));
    }

    return result;
}

}
