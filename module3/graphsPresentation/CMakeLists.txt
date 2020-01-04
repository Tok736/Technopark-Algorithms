cmake_minimum_required(VERSION 3.15)
project(graphsPresentation)

set(CMAKE_CXX_STANDARD 14)


include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/interfaces)

file(GLOB_RECURSE
        CPPS "source/*.cpp")

add_executable(${PROJECT_NAME} ${CPPS} main.cpp)