cmake_minimum_required(VERSION 3.10)
project(FaultyDisk)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-std=c++17 -O3 ${CMAKE_CXX_FLAGS}")

add_executable(FaultyDisk main.cpp Utility.hpp Utility.cpp Algorithms.cpp Algorithms.hpp)

add_executable(Playground testMain.cpp Utility.hpp Utility.cpp Algorithms.cpp Algorithms.hpp)