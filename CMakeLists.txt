cmake_minimum_required(VERSION 4.2)
project(STL3DLooker)

set(CMAKE_CXX_STANDARD 20)

add_executable(STL3DLooker main.cpp
        math.hpp readSTL.hpp)
target_include_directories(STL3DLooker PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})