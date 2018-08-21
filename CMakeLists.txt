cmake_minimum_required (VERSION 3.5)

PROJECT (GLEngine)
SET (GLEngine_VERSION_MAJOR 0)
SET (GLEngine_VERSION_MINOR 0)
SET (GLEngine_VERSION_PATCH 0)

SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++17")

SET (source_dir "${PROJECT_SOURCE_DIR}/src")
SET (header_dir "${PROJECT_SOURCE_DIR}/include")
SET (test_dir "${PROJECT_SOURCE_DIR}/test")

FILE (GLOB source_files "${source_dir}/*.cpp")
FILE (GLOB header_files "${header_dir}/*.hpp" "${header_dir}/*.h")

SET (EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")
#SET (LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/lib")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("${PROJECT_SOURCE_DIR}/glfw/")

ADD_EXECUTABLE (GLEngine ${source_files} ${header_files})

TARGET_LINK_LIBRARIES (GLEngine glfw)
TARGET_INCLUDE_DIRECTORIES (GLEngine PRIVATE ${header_dir})
