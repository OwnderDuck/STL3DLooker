cmake_minimum_required(VERSION 4.2)
project(STL3DLooker)

set(CMAKE_CXX_STANDARD 20)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/cube.stl
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(STL3DLooker main.cpp
        math.hpp readSTL.hpp
        canvas.cpp)
target_include_directories(STL3DLooker PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

option(BUILD_TESTING "Build the testing suite" ON)

if(BUILD_TESTING)
    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/refs/heads/main.zip
    )
    FetchContent_MakeAvailable(googletest)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    enable_testing()
    add_executable(unit_tests test.cpp)
    target_link_libraries(unit_tests GTest::gtest_main)
    target_include_directories(unit_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

    add_test(NAME AllMathTests COMMAND unit_tests)
endif()