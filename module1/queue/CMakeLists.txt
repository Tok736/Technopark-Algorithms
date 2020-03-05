cmake_minimum_required(VERSION 3.15)
project(queue)

SET(MYCOMPILE_FLAGS "-Werror -lm")
set(CMAKE_CPP_STANDARD 14)

add_executable(queue main.cpp)

