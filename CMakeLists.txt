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

# Day 3
file(   COPY ${CMAKE_CURRENT_SOURCE_DIR}/day_3/input_3.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_executable(puzzle_5 day_3/puzzle_1/main.cpp)
add_executable(puzzle_6 day_3/puzzle_2/main.cpp)

# Day 4
file(   COPY ${CMAKE_CURRENT_SOURCE_DIR}/day_4/input_4.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_executable(puzzle_7 day_4/puzzle_1/main.cpp)
add_executable(puzzle_8 day_4/puzzle_2/main.cpp)

# Day 5
file(   COPY ${CMAKE_CURRENT_SOURCE_DIR}/day_5/input_5.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_executable(puzzle_9 day_5/puzzle_1/main.cpp)
add_executable(puzzle_10 day_5/puzzle_2/main.cpp)

# Day 6
file(   COPY ${CMAKE_CURRENT_SOURCE_DIR}/day_6/input_6.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_executable(puzzle_11 day_6/puzzle_1/main.cpp)
add_executable(puzzle_12 day_6/puzzle_2/main.cpp)

# Day 7
file(   COPY ${CMAKE_CURRENT_SOURCE_DIR}/day_7/input_7.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_executable(puzzle_13 day_7/puzzle_1/main.cpp)
add_executable(puzzle_14 day_7/puzzle_2/main.cpp)