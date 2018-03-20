cmake_minimum_required(VERSION 3.9)
project(colors)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(colors main.cpp color.hpp numbers.hpp)
