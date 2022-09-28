cmake_minimum_required(VERSION 3.10)

# set project name
project(GLEngine)

# specify the C++ standard (note alt. for Windows)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# Policy related to legacy OpenGL/version selection
set(CMAKE_POLICY_DEFAULT_CMP0072 NEW)

# dependencies
add_subdirectory(CPPML build/CPPML)

set (GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set (GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set (GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw build/glfw)

add_subdirectory(glew-2.1.0/build/cmake build/glew)

# find all source files
file (GLOB_RECURSE source_files "src/*.cpp")

# add library
add_library(GLEngine ${source_files})

target_link_libraries(GLEngine PUBLIC CPPML glfw glew)
target_include_directories(GLEngine PUBLIC
    ./include/
    ./spdlog-1.9.2/include/
    ./glew-2.1.0/include/
    ./glfw/include/
    ./CPPML/include/
    ./include/imgui/
)