cmake_minimum_required(VERSION 3.17)
project(string_project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(string_project
        l_string.cpp
        l_string.h
        main.cpp)

