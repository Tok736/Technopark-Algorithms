cmake_minimum_required(VERSION 3.15)
project(unimodal)

set(CMAKE_CXX_STANDARD 14)
SET(MYCOMPILE_FLAGS "-Werror -lm")

add_executable(unimodal main.cpp)