cmake_minimum_required (VERSION 3.16.3)
project (TEST)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++17")

add_subdirectory (src)
add_subdirectory (test)
