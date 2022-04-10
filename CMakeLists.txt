cmake_minimum_required (VERSION 3.16.3)
project (TEST)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++17")

set(CMAKE_POLICY_DEFAULT_CMP0072 NEW)

add_subdirectory (src)
add_subdirectory (test)
