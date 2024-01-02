cmake_minimum_required(VERSION 3.27)
project(Leopold)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_library(Leopold STATIC
        Manille.cpp
        Manille.hpp
        Card.hpp
        State.hpp
        State.cpp
        Agent.cpp
)


enable_testing()

add_executable(
        tests
        tests/ManilleTests.cpp
        tests/CardTests.cpp
        tests/StateTests.cpp
        tests/AgentTests.cpp
)


target_link_libraries(
        tests
        GTest::gtest_main
        Leopold
)

include(GoogleTest)
gtest_discover_tests(tests)
