#pragma once

#include <concepts>
#include <charconv>
#include <string>

namespace aoc {

template <typename T>
struct converter {
    T operator()(std::string_view str) = delete;
};

template <>
struct converter<std::string> {
    std::string operator()(std::string const& str) {
        return str;
    }
};


template <typename T>
requires (std::signed_integral<T> || std::unsigned_integral<T>)
struct converter<T> {
    T operator()(std::string_view str) {
        T result;
        std::from_chars(str.data(), str.data() + str.size(), result);
        return result;
    }
};

}
