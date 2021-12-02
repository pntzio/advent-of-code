#pragma once

#include <chrono>
#include <iostream>
#include <string_view>
#include <functional>
#include <filesystem>

namespace aoc {

struct problem {
    using clock_t = std::chrono::high_resolution_clock;

    std::string_view year;
    std::string_view day;
    std::filesystem::path input_path;
    std::function<void(std::filesystem::path)> part_a;
    std::function<void(std::filesystem::path)> part_b;

    void execute_a() {
        std::cout << "=========================\n"
                  << "Executing " << year << "/" << day << "/1" << std::endl;

        clock_t::time_point start = clock_t::now();
        part_a(input_path);
        clock_t::time_point stop = clock_t::now();

        std::cout << "Execution took "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " ms\n"
                  << "=========================" << std::endl;
    }

    void execute_b() {
        std::cout << "=========================\n"
                  << "Executing " << year << "/" << day << "/2" << std::endl;

        clock_t::time_point start = clock_t::now();
        part_b(input_path);
        clock_t::time_point stop = clock_t::now();

        std::cout << "Execution took "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " ms\n"
                  <<"=========================" << std::endl;
    }

    void execute_all() {
        execute_a();
        execute_b();
    }
};

}
