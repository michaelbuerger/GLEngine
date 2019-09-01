cmake_minimum_required (VERSION 3.5)

project (GLEngine)
set (GLEngine_VERSION_MAJOR 0)
set (GLEngine_VERSION_MINOR 1)
set (GLEngine_VERSION_PATCH 0)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++17")

set (source_dir "${PROJECT_SOURCE_DIR}/src")
set (header_dir "${PROJECT_SOURCE_DIR}/include")
set (test_dir "${PROJECT_SOURCE_DIR}/test")

file (GLOB_RECURSE source_files "${source_dir}/*.cpp")

set (EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

set (GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set (GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set (GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory ("${PROJECT_SOURCE_DIR}/glfw/")

add_subdirectory ("${PROJECT_SOURCE_DIR}/glew-2.1.0/build/cmake/")

add_executable (GLEngine ${source_files})

target_link_libraries (GLEngine glfw glew ${PROJECT_SOURCE_DIR}/CPPModelLibrary/libCPPModelLibrary.a)
target_include_directories (
	GLEngine PRIVATE
	include/
	glfw/include/
	glew-2.1.0/include/
	spdlog-1.x/include/
	CPPModelLibrary/include/
	include/imgui/
)
