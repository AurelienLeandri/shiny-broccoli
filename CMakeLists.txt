cmake_minimum_required(VERSION 3.0)

project(ShinyBroccoli)

# C++14 and extra flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wextra -lpthread -std=c++1y -O3")

# Sets library output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/samples)

include_directories(
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/test
        ${CMAKE_SOURCE_DIR}/samples
)

# Adds source directory
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(samples)
