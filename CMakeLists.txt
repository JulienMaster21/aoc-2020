cmake_minimum_required(VERSION 3.17)
project(aoc_2020)

set(CMAKE_CXX_STANDARD 20)

# Day 1
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/day_1)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/day_1)
file(   COPY ${CMAKE_CURRENT_SOURCE_DIR}/day_1/input.txt
        DESTINATION ${EXECUTABLE_OUTPUT_PATH})
add_executable(puzzle_1 day_1/puzzle_1/main.cpp)
add_executable(puzzle_2 day_1/puzzle_2/main.cpp)