cmake_minimum_required(VERSION 3.27)
project(Leopold_I)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_library(Leopold_I STATIC
        Manille.cpp
        Manille.hpp
        Card.hpp
)


enable_testing()

add_executable(
        manille_test
        tests/ManilleTests.cpp
        tests/CardTests.cpp
)
target_link_libraries(
        manille_test
        GTest::gtest_main
        Leopold_I
)

include(GoogleTest)
gtest_discover_tests(manille_test)
