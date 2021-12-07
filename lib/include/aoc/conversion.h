#pragma once

#include <stdexcept>
#include <concepts>
#include <charconv>
#include <string>
#include <sstream>
#include <bitset>

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

template <std::size_t N>
struct converter<std::bitset<N>> {
    std::bitset<N> operator()(std::string const& str) {
        return std::bitset<N>(str);
    }
};

template <typename T>
requires (std::signed_integral<T> || std::unsigned_integral<T>)
struct converter<T> {
    T operator()(std::string_view str) {
        T result;
        auto [ptr, ec] { std::from_chars(str.data(), str.data() + str.size(), result) };

        if(ec != std::errc{}) {
            std::stringstream ss;
            ss << "Failed to convert text to integral type. (Text = '" << str << "')";
            throw std::runtime_error(ss.str());
        }

        return result;
    }
};

}
