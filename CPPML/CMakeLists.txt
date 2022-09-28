cmake_minimum_required (VERSION 3.10)

# specify the C++ standard (note alt. for Windows)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# specify CPPML as library
add_library(CPPML src/Loading.cpp src/Log.cpp src/OBJ.cpp src/Useful.cpp)

# include directory
target_include_directories(CPPML PUBLIC ./include spdlog-1.9.2/include)