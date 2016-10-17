cmake_minimum_required(VERSION 3.6)
project(ap3_ex1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES mlistLL.c mentry.c)
add_executable(ap3_ex1 ${SOURCE_FILES})
add_executable(kentest kentest.c mentry.c)