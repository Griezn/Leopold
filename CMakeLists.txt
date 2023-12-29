cmake_minimum_required(VERSION 3.27)
project(Leopold_I)

set(CMAKE_CXX_STANDARD 20)

add_executable(Leopold_I main.cpp
        Manille.cpp
        Manille.hpp
        Card.hpp
        Agent.cpp
        Agent.hpp
        tests/ManilleTests.cpp
        tests/AgentTests.cpp
)
