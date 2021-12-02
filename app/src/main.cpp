#include <iostream>
#include <array>
#include <functional>

#include "aoc/execution.h"
#include "everything.h"

std::array<aoc::executor, 5> problems {{
    { "2021", "01", aoc::problem{std::bind(y21d01::part_a, std::placeholders::_1), std::bind(y21d01::part_b, std::placeholders::_1)} },
    { "2021", "02", aoc::problem{std::bind(y21d02::part_a, std::placeholders::_1), std::bind(y21d02::part_b, std::placeholders::_1)} },
    { "2021", "02", aoc::problem{std::bind(y21d03::part_a, std::placeholders::_1), std::bind(y21d03::part_b, std::placeholders::_1)} },
    { "2021", "02", aoc::problem{std::bind(y21d04::part_a, std::placeholders::_1), std::bind(y21d04::part_b, std::placeholders::_1)} },
    { "2021", "02", aoc::problem{std::bind(y21d05::part_a, std::placeholders::_1), std::bind(y21d05::part_b, std::placeholders::_1)} }
}};

int main(int argc, char* argv[]) {

    problems[1].problem.part_b("./inputs/2021/02.txt");

    return 0;
}
