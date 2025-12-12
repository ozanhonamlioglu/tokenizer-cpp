cmake_minimum_required(VERSION 3.30.5)
project(tokenizer_cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(tokenizer_cpp
        main.cpp
        tokenizer.cpp
        tokenizer.hpp
        utils.hpp
        utils.cpp
        performance.cpp
        performance.hpp
)
