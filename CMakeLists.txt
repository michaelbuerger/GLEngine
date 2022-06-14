cmake_minimum_required (VERSION 3.16.3)
project (TEST)


if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang") # linux
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
else() # windows
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
    add_compile_definitions(GLEW_STATIC)
endif()

set(CMAKE_POLICY_DEFAULT_CMP0072 NEW)


add_subdirectory (src)
add_subdirectory (test)
