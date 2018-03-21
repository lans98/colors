cmake_minimum_required(VERSION 3.9)
project(colors)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(.)

add_executable(colors main.cpp)
add_executable(echoterm echo_terminal.cpp)
