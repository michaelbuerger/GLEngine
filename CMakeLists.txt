cmake_minimum_required (VERSION 3.5)

PROJECT (GLEngine)
SET (GLEngine_VERSION_MAJOR 0)
SET (GLEngine_VERSION_MINOR 0)
SET (GLEngine_VERSION_PATCH 0)

SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++17")

SET (source_dir "${PROJECT_SOURCE_DIR}/src")
SET (test_dir "${PROJECT_SOURCE_DIR}/test")

FILE (GLOB_RECURSE source_files "${source_dir}/*.cpp")

SET (EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("${PROJECT_SOURCE_DIR}/glfw/")
add_subdirectory("${PROJECT_SOURCE_DIR}/glew-2.1.0/build/cmake")

ADD_EXECUTABLE (GLEngine ${source_files} ${header_files})

TARGET_LINK_LIBRARIES (GLEngine glfw glew)
TARGET_INCLUDE_DIRECTORIES(
	GLEngine PRIVATE
	include
	glfw/include
	glew-2.1.0/include
)
