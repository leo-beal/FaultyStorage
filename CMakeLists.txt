cmake_minimum_required(VERSION 3.10)
project(FaultyDisk)

set(CMAKE_CXX_STANDARD 17)

add_executable(FaultyDisk main.cpp Utility.hpp Utility.cpp)

add_executable(Playground testMain.cpp Utility.hpp Utility.cpp)