cmake_minimum_required(VERSION 3.6)
project(ap3_ex1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(finddupl finddupl.c mentry.c mlist.c)
add_executable(findduplLL finddupl.c mentry.c mlistLL.c)
add_executable(generate_input generate_input.c)