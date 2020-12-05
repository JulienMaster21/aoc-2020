cmake_minimum_required(VERSION 3.17)
project(aoc_2020)

set(CMAKE_CXX_STANDARD 20)

# Day 1
file(   COPY ${CMAKE_CURRENT_SOURCE_DIR}/day_1/input_1.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_executable(puzzle_1 day_1/puzzle_1/main.cpp)
add_executable(puzzle_2 day_1/puzzle_2/main.cpp)

# Day 2
file(   COPY ${CMAKE_CURRENT_SOURCE_DIR}/day_2/input_2.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_executable(puzzle_3 day_2/puzzle_1/main.cpp)
add_executable(puzzle_4 day_2/puzzle_2/main.cpp)