cmake_minimum_required(VERSION 3.0)

project(AOC_2020 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")

include_directories(include solutions)

set(AOC_SOURCE
    src/Utilities.cpp
)

get_filename_component(INPUT_FILE_PATH "inputs" REALPATH BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
configure_file(include/InputDirectoryConfig.ipp.in ${CMAKE_BINARY_DIR}/generated/InputDirectoryConfig.ipp)
include_directories(${CMAKE_BINARY_DIR}/generated/)

set(AOC_SOURCE_H
    include/Export.hpp
    include/Utilities.ipp
    include/InputDirectoryConfig.ipp
)

add_library(AOC SHARED 
    ${AOC_SOURCE_H}
    ${AOC_SOURCE}
)

add_subdirectory(solutions)