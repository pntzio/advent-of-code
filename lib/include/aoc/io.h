#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

#include "aoc/conversion.h"

namespace aoc {

template <typename T = std::string>
std::vector<T> read_file_lines(std::filesystem::path path) {
    std::vector<T> result;
    std::ifstream stream(path);
    std::string line;

    while(std::getline(stream, line)) {
        result.push_back(converter<T>()(line));
    }

    return result;
}

}
