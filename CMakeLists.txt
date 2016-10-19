cmake_minimum_required(VERSION 3.6)
project(ap3_ex1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(ap3_ex1 finddupl.c mentry.c mlist.c)
add_executable(ap3_ex1_LL finddupl.c mentry.c mlistLL.c)
add_executable(kentest kentest.c mentry.c)