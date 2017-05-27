cmake_minimum_required(VERSION 3.7)
project(matrac)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s -O3")

set(SOURCE_FILES main.cpp SobolGenerator.cpp SobolGenerator.hpp)
add_executable(matrac ${SOURCE_FILES})