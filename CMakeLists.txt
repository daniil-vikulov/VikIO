cmake_minimum_required(VERSION 3.22)
project(VikIO)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)
add_executable(VikIO main.cpp tests/Tests.cpp)
