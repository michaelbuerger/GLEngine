cmake_minimum_required (VERSION 3.5)

project (GLEngine)
set (GLEngine_VERSION_MAJOR 0)
set (GLEngine_VERSION_MINOR 0)
set (GLEngine_VERSION_PATCH 0)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++11")

set (source_dir "${PROJECT_SOURCE_DIR}/src")
set (header_dir "${PROJECT_SOURCE_DIR}/include")
set (test_dir "${PROJECT_SOURCE_DIR}/test")

file (GLOB_RECURSE source_files "${source_dir}/*.cpp")
file (GLOB_RECURSE header_files "${header_dir}/*.hpp" "${header_dir}/*.h")

set (EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

set (GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set (GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set (GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory ("${PROJECT_SOURCE_DIR}/glfw/")

add_subdirectory ("${PROJECT_SOURCE_DIR}/glew-2.1.0/build/cmake/")
add_subdirectory ("${PROJECT_SOURCE_DIR}/spdlog-1.x/")

add_executable (GLEngine ${source_files} ${header_files})

target_link_libraries (GLEngine glfw glew)
target_include_directories (
	GLEngine PRIVATE
	include/
	glfw/include/
	glew-2.1.0/include/
	spdlog-1.x/include/
)
