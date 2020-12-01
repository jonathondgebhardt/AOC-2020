cmake_minimum_required(VERSION 3.0)

project(AOC_2020 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")

include_directories(include)

set(AOC_SOURCE
    src/InputParser.cpp
)

set(AOC_SOURCE_H
    include/Export.hpp
    include/InputParser.hpp
)

add_library(AOC SHARED 
    ${AOC_SOURCE_H}
    ${AOC_SOURCE}
)

add_subdirectory(day1)