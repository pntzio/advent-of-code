#pragma once

#include <numeric>
#include <filesystem>
#include <iterator>
#include <optional>

#include "aoc/io.h"
#include "aoc/problem.h"

namespace d04 {

struct bingo_number {
    std::uint32_t value = 0;
    bool          is_marked = false;
};

class bingo_board {

public:

    bingo_board(std::array<std::array<bingo_number, 5>,5> const& numbers) {
        numbers_ = numbers;
    }

    void mark(std::uint32_t number) {
        for(std::size_t row = 0; row < numbers_.size(); row++) {
            for(std::size_t col = 0; col < numbers_.size(); col++) {
                bingo_number& bn = numbers_[row][col];

                if(bn.value == number) {
                    bn.is_marked = true;
                }
            }
        }
    }

    std::optional<std::uint32_t> winning_sum() const {
        auto winning_row = winning_row_index();
        auto winning_col = winning_col_index();

        if(winning_row.has_value() || winning_col.has_value()) {
            return unmarked_sum();
        }

        return {};
    }

private:

    std::uint32_t unmarked_sum() const {
        std::uint32_t sum = 0;
        for(std::size_t row = 0; row < numbers_.size(); row++) {
            for(std::size_t col = 0; col < numbers_.size(); col++) {
                bingo_number const& bn = numbers_[row][col];
                sum += (bn.is_marked ? 0 : bn.value);
            }
        }

        return sum;
    }

    std::optional<std::size_t> winning_row_index() const {
        for(std::size_t row = 0; row < numbers_.size(); row++) {
            bool is_winning = std::all_of(numbers_[row].cbegin(), numbers_[row].cend(), [](bingo_number const& n) {
                return n.is_marked;
            });

            if(is_winning) {
                return row;
            }
        }

        return {};
    }

    std::optional<std::size_t> winning_col_index() const {
        for(std::size_t col = 0; col < numbers_.size(); col++) {
            if(numbers_[0][col].is_marked &&
               numbers_[1][col].is_marked &&
               numbers_[2][col].is_marked &&
               numbers_[3][col].is_marked &&
               numbers_[4][col].is_marked) {
                return col;
            }
        }

        return {};
    }

    std::array<std::array<bingo_number, 5>,5> numbers_;

};

template <typename InputIt>
std::array<std::array<bingo_number, 5>,5> parse_board(InputIt first, InputIt last) {
    std::array<std::array<bingo_number, 5>,5> result;
    std::uint32_t row = 0;
    std::uint32_t col = 0;

    for(auto it = first; it != last; it++) {
        auto numbers = aoc::split_string<std::uint32_t>(*it);
        //auto numbers = parse_space_numbers(*it);

        for(std::uint32_t num : numbers) {
            result[row][col].value = num;
            col++;
        }
        row++;
        col = 0;
    }

    return result;
}

template <typename InputIt>
std::vector<bingo_board> parse_boards(InputIt first, InputIt last) {
    std::vector<bingo_board> boards;
    for(auto it = first; it != last; it += 5) {
        auto board_numbers = parse_board(it, std::next(it, 5));
        boards.push_back(bingo_board(board_numbers));
    }

    return boards;
}

void part_a(std::filesystem::path input_path) {
    std::vector<std::string> lines = aoc::read_file_lines(input_path);
    std::vector<std::uint32_t> drawn_numbers = aoc::split_string<std::uint32_t>(lines[0], ',');
    std::vector<bingo_board> boards = parse_boards(std::next(lines.begin()), lines.end());

    std::optional<std::uint32_t> winning_sum;

    for(std::uint32_t num : drawn_numbers) {
        for(auto& board : boards) {
            board.mark(num);

            winning_sum = board.winning_sum();
            if(winning_sum.has_value()) {
                std::cout << winning_sum.value() * num << std::endl;
                break;
            }
        }

        if(winning_sum.has_value()) {
            break;
        }
    }
}

void part_b(std::filesystem::path input_path) {
    std::vector<std::string> lines = aoc::read_file_lines(input_path);
    std::vector<std::uint32_t> drawn_numbers = aoc::split_string<std::uint32_t>(lines[0], ',');
    std::vector<bingo_board> tmp_boards = parse_boards(std::next(lines.begin()), lines.end());
    std::vector<std::pair<bool, bingo_board>> boards;

    for(auto& b : tmp_boards) {
        boards.push_back(std::make_pair(false, b));
    }

    bool done = false;

    for(std::uint32_t num : drawn_numbers) {
        for(auto& board : boards) {
            if(board.first) {
                continue;
            }

            board.second.mark(num);
            if(board.second.winning_sum().has_value()) {
                board.first = true;
            }

            if(std::all_of(boards.cbegin(), boards.cend(), [](std::pair<bool, bingo_board> const& b) {
                return b.first;
            })) {
                std::cout << board.second.winning_sum().value() * num << std::endl;
                done = true;
                break;
            }
        }

        if(done) {
            break;
        }
    }
}

}
